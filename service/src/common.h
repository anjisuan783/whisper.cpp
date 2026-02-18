#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <mutex>
#include <condition_variable>

#define WHISPER_SERVICE_VERSION "1.0.0"
#define WHISPER_SERVICE_NAME "whisper-rknn-service"

#define DEFAULT_PORT 10095
#define DEFAULT_MAX_AUDIO_SEC 20
#define DEFAULT_LANGUAGE "zh"
#define DEFAULT_SAMPLE_RATE 16000
#define DEFAULT_AUDIO_FORMAT "wav"

enum AudioFormat {
    AUDIO_FORMAT_UNKNOWN = 0,
    AUDIO_FORMAT_WAV = 1,
    AUDIO_FORMAT_PCM = 2
};

struct ServiceConfig {
    int port = DEFAULT_PORT;
    std::string model_dir = "./models";
    std::string default_lang = DEFAULT_LANGUAGE;
    int max_audio_sec = DEFAULT_MAX_AUDIO_SEC;
    bool verbose = false;
};

enum ErrorCode {
    ERR_SUCCESS = 0,
    ERR_INVALID_REQUEST = 1001,
    ERR_MODEL_LOAD_FAILED = 1002,
    ERR_AUDIO_FORMAT_ERROR = 1003,
    ERR_AUDIO_TOO_LONG = 1004,
    ERR_INFERENCE_FAILED = 1005,
    ERR_INTERNAL_ERROR = 1006
};

inline const char* get_error_message(ErrorCode code) {
    switch (code) {
        case ERR_SUCCESS: return "success";
        case ERR_INVALID_REQUEST: return "invalid request";
        case ERR_MODEL_LOAD_FAILED: return "model load failed";
        case ERR_AUDIO_FORMAT_ERROR: return "audio format error";
        case ERR_AUDIO_TOO_LONG: return "audio too long";
        case ERR_INFERENCE_FAILED: return "inference failed";
        case ERR_INTERNAL_ERROR: return "internal error";
        default: return "unknown error";
    }
}

#endif
