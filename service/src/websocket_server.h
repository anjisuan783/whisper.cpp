#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <string>
#include <functional>
#include <memory>
#include <libwebsockets.h>
#include "common.h"
#include "protocol.h"
#include "audio_buffer.h"

struct lws_context;
struct lws;

enum SessionState {
    SESSION_INIT = 0,
    SESSION_CONFIG_RECEIVED = 1,
    SESSION_RECEIVING_AUDIO = 2,
    SESSION_FINISHED = 3
};

struct ClientSession {
    lws* wsi;
    SessionState state;
    FunasrMessage config;
    AudioBuffer audio_buffer;
    std::string reqid;
    
    ClientSession() : wsi(nullptr), state(SESSION_INIT) {}
};

class WebSocketServer {
public:
    using TranscribeCallback = std::function<ErrorCode(const std::vector<float>&, const std::string&, std::string&)>;
    
    WebSocketServer(const ServiceConfig& config);
    ~WebSocketServer();
    
    void set_transcribe_callback(TranscribeCallback callback) { transcribe_callback_ = callback; }
    bool start();
    void stop();
    void run();
    bool is_running() const { return running_; }
    
    // 公开处理消息方法供静态回调使用
    void handle_message(ClientSession* session, struct lws* wsi, void* in, size_t len);
    
    static int callback_websocket(struct lws *wsi, enum lws_callback_reasons reason,
                                   void *user, void *in, size_t len);
    
private:
    ServiceConfig config_;
    lws_context* context_;
    volatile bool running_;
    TranscribeCallback transcribe_callback_;
    
    void handle_config(ClientSession* session, const std::string& json_str);
    void handle_audio_data(ClientSession* session, const uint8_t* data, size_t len);
    void handle_finish(ClientSession* session);
    void send_response(ClientSession* session, const std::string& response);
};

#endif
