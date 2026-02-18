#include "websocket_server.h"
#include <iostream>
#include <cstring>

static WebSocketServer* g_server_instance = nullptr;

static int lws_callback(struct lws *wsi, enum lws_callback_reasons reason, 
                        void *user, void *in, size_t len) {
    ClientSession* session = (ClientSession*)user;
    
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            std::cout << "Client connected" << std::endl;
            memset(session, 0, sizeof(ClientSession));
            session->wsi = wsi;
            session->state = SESSION_INIT;
            break;
            
        case LWS_CALLBACK_CLOSED:
            std::cout << "Client disconnected" << std::endl;
            break;
            
        case LWS_CALLBACK_RECEIVE:
            if (g_server_instance && session) {
                g_server_instance->handle_message(session, wsi, in, len);
            }
            break;
            
        default:
            break;
    }
    return 0;
}

WebSocketServer::WebSocketServer(const ServiceConfig& config) 
    : config_(config), context_(nullptr), running_(false) {
}

WebSocketServer::~WebSocketServer() {
    stop();
}

bool WebSocketServer::start() {
    static struct lws_protocols protocols[] = {
        { "funasr-protocol", lws_callback, sizeof(ClientSession), 65536 },
        { nullptr, nullptr, 0, 0 }
    };
    
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));
    info.port = config_.port;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;
    
    context_ = lws_create_context(&info);
    if (!context_) {
        std::cerr << "Failed to create WebSocket context" << std::endl;
        return false;
    }
    
    g_server_instance = this;
    running_ = true;
    std::cout << "WebSocket server started on port " << config_.port << std::endl;
    return true;
}

void WebSocketServer::stop() {
    running_ = false;
    if (context_) {
        lws_context_destroy(context_);
        context_ = nullptr;
    }
    g_server_instance = nullptr;
}

void WebSocketServer::run() {
    while (running_ && context_) {
        lws_service(context_, 50);
    }
}

void WebSocketServer::handle_message(ClientSession* session, struct lws* wsi, void* in, size_t len) {
    if (!in || len == 0) return;
    
    uint8_t* data = (uint8_t*)in;
    
    bool is_binary = (lws_frame_is_binary(wsi) != 0);
    
    if (is_binary) {
        std::cout << "Audio: " << len << " bytes" << std::endl;
        handle_audio_data(session, data, len);
    } else {
        std::string json_str((char*)data, len);
        std::cout << "JSON: " << json_str << std::endl;
        
        if (is_finish_message(json_str)) {
            handle_finish(session);
        } else {
            handle_config(session, json_str);
        }
    }
}

void WebSocketServer::handle_config(ClientSession* session, const std::string& json_str) {
    std::string error;
    if (!parse_funasr_config(json_str, session->config, error)) {
        send_response(session, build_error_response("", ERR_INVALID_REQUEST, error));
        return;
    }
    
    // session->reqid = session->config.reqid;
    session->state = SESSION_CONFIG_RECEIVED;
    session->audio_buffer.reset();
    
    std::cout << "JSON string: " << json_str << std::endl; std::cout << "Config: reqid=" << session->reqid << std::endl;
}

void WebSocketServer::handle_audio_data(ClientSession* session, const uint8_t* data, size_t len) {
    if (session->state != SESSION_CONFIG_RECEIVED && 
        session->state != SESSION_RECEIVING_AUDIO) {
        return;
    }
    
    session->audio_buffer.append(data, len);
    session->state = SESSION_RECEIVING_AUDIO;
}

void WebSocketServer::handle_finish(ClientSession* session) {
    if (session->state != SESSION_RECEIVING_AUDIO) {
        send_response(session, build_error_response(session->reqid, 
            ERR_INVALID_REQUEST, "no audio data"));
        return;
    }
    
    std::vector<float> pcm_data;
    int sample_rate = 0;
    ErrorCode err;
    
    AudioFormat format = session->audio_buffer.detect_format();
    if (format == AUDIO_FORMAT_WAV) {
        err = session->audio_buffer.parse_wav(pcm_data, sample_rate);
    } else { // binary
        err = session->audio_buffer.get_pcm_data(pcm_data);
        sample_rate = DEFAULT_SAMPLE_RATE;
    }
    
    if (err != ERR_SUCCESS) {
        send_response(session, build_error_response(session->reqid, err));
        return;
    }
    
    float duration = (float)pcm_data.size() / sample_rate;
    if (duration > config_.max_audio_sec) {
        send_response(session, build_error_response(session->reqid, ERR_AUDIO_TOO_LONG));
        return;
    }
    
    std::string result;
    std::string lang = session->config.wav_name.empty() ? 
                       config_.default_lang : session->config.wav_name;
    if (transcribe_callback_) {
        err = transcribe_callback_(pcm_data, lang, result);
    } else { // binary
        err = ERR_INTERNAL_ERROR;
    }
    
    std::string response;
    if (err == ERR_SUCCESS) {
        response = build_funasr_response(session->reqid, ERR_SUCCESS, "success", result);
    } else { // binary
        response = build_error_response(session->reqid, err);
    }
    
    send_response(session, response);
    session->state = SESSION_FINISHED;
}

void WebSocketServer::send_response(ClientSession* session, const std::string& response) { std::cout << "Sending response: " << response << std::endl;
    if (!session || !session->wsi) return;
    
    uint8_t* buf = new uint8_t[LWS_PRE + response.size()];
    memcpy(&buf[LWS_PRE], response.c_str(), response.size());
    lws_write(session->wsi, &buf[LWS_PRE], response.size(), LWS_WRITE_TEXT);
    delete[] buf;
    
    std::cout << "Response sent" << std::endl;
}

int WebSocketServer::callback_websocket(struct lws *wsi, enum lws_callback_reasons reason,
                                         void *user, void *in, size_t len) {
    return lws_callback(wsi, reason, user, in, len);
}
