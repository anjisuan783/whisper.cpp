#include <iostream>
#include <string>
#include <memory>
#include <signal.h>
#include "common.h"
#include "websocket_server.h"
#include "whisper_handler.h"

static volatile bool g_running = true;
static std::unique_ptr<WebSocketServer> g_server;
static std::unique_ptr<WhisperHandler> g_whisper;

void signal_handler(int sig) {
    std::cout << "\nReceived signal " << sig << ", shutting down..." << std::endl;
    g_running = false;
    if (g_server) {
        g_server->stop();
    }
}

void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --port <port>         WebSocket port (default: 10095)" << std::endl;
    std::cout << "  --model-dir <path>    Model directory (default: ./models)" << std::endl;
    std::cout << "  --lang <en|zh>        Default language (default: zh)" << std::endl;
    std::cout << "  --max-audio-sec <n>   Max audio duration in seconds (default: 20)" << std::endl;
    std::cout << "  --help                Show this help" << std::endl;
}

ServiceConfig parse_args(int argc, char* argv[]) {
    ServiceConfig config;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--port" && i + 1 < argc) {
            config.port = std::stoi(argv[++i]);
        } else if (arg == "--model-dir" && i + 1 < argc) {
            config.model_dir = argv[++i];
        } else if (arg == "--lang" && i + 1 < argc) {
            config.default_lang = argv[++i];
        } else if (arg == "--max-audio-sec" && i + 1 < argc) {
            config.max_audio_sec = std::stoi(argv[++i]);
        } else if (arg == "--verbose") {
            config.verbose = true;
        } else if (arg == "--help") {
            print_usage(argv[0]);
            exit(0);
        }
    }
    
    return config;
}

int main(int argc, char* argv[]) {
    std::cout << "Whisper RKNN WebSocket Service v" << WHISPER_SERVICE_VERSION << std::endl;
    
    // 解析参数
    ServiceConfig config = parse_args(argc, argv);
    
    std::cout << "Configuration:" << std::endl;
    std::cout << "  Port: " << config.port << std::endl;
    std::cout << "  Model dir: " << config.model_dir << std::endl;
    std::cout << "  Language: " << config.default_lang << std::endl;
    std::cout << "  Max audio: " << config.max_audio_sec << " seconds" << std::endl;
    
    // 设置信号处理
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    // 初始化Whisper
    g_whisper = std::make_unique<WhisperHandler>();
    
    std::string encoder_path = config.model_dir + "/whisper_encoder_base_20s.rknn";
    std::string decoder_path = config.model_dir + "/whisper_decoder_base_20s.rknn";
    std::string vocab_path = config.model_dir + "/vocab_" + config.default_lang + ".txt";
    std::string mel_filters_path = config.model_dir + "/mel_80_filters.txt";
    
    std::cout << "Initializing Whisper models..." << std::endl;
    std::cout << "  Encoder: " << encoder_path << std::endl;
    std::cout << "  Decoder: " << decoder_path << std::endl;
    std::cout << "  Vocab: " << vocab_path << std::endl;
    
    ErrorCode err = g_whisper->initialize(encoder_path, decoder_path, 
                                           vocab_path, mel_filters_path);
    if (err != ERR_SUCCESS) {
        std::cerr << "Failed to initialize Whisper: " << get_error_message(err) << std::endl;
        return 1;
    }
    
    std::cout << "Whisper initialized: " << g_whisper->get_status() << std::endl;
    
    // 创建WebSocket服务器
    g_server = std::make_unique<WebSocketServer>(config);
    
    // 设置转写回调
    g_server->set_transcribe_callback(
        [](const std::vector<float>& pcm_data, const std::string& lang, std::string& result) {
            return g_whisper->transcribe(pcm_data, lang, result);
        }
    );
    
    // 启动服务器
    if (!g_server->start()) {
        std::cerr << "Failed to start WebSocket server" << std::endl;
        return 1;
    }
    
    std::cout << "Service ready. Press Ctrl+C to stop." << std::endl;
    
    // 运行事件循环
    g_server->run();
    
    std::cout << "Service stopped." << std::endl;
    return 0;
}
