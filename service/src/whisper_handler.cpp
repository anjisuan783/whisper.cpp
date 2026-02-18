#include "whisper_handler.h"
#include <cstring>
#include <fstream>
#include <iostream>

extern int init_whisper_model(const char* model_path, rknn_app_context_t* app_ctx);
extern int release_whisper_model(rknn_app_context_t* app_ctx);
extern int inference_whisper_model(rknn_whisper_context_t* app_ctx, 
                                    std::vector<float> audio_data, 
                                    float* mel_filters, 
                                    VocabEntry* vocab, 
                                    int task_code, 
                                    std::vector<std::string>& recognized_text);
extern void audio_preprocess(audio_buffer_t* audio, float* mel_filters, std::vector<float>& x_mel);
extern int read_mel_filters(const char* fileName, float* data, int max_lines);
extern int read_vocab(const char* fileName, VocabEntry* vocab);

WhisperHandler::WhisperHandler() : initialized_(false), ctx_(nullptr) {
    vocab_.resize(VOCAB_NUM);
    mel_filters_.resize(N_MELS * MELS_FILTERS_SIZE);
}

WhisperHandler::~WhisperHandler() {
    if (initialized_ && ctx_) {
        release_whisper_model(&ctx_->encoder_context);
        release_whisper_model(&ctx_->decoder_context);
        delete ctx_;
    }
    for (auto& entry : vocab_) {
        if (entry.token) {
            free(entry.token);
            entry.token = nullptr;
        }
    }
}

ErrorCode WhisperHandler::initialize(const std::string& encoder_path,
                                      const std::string& decoder_path,
                                      const std::string& vocab_path,
                                      const std::string& mel_filters_path) {
    vocab_path_ = vocab_path;
    mel_filters_path_ = mel_filters_path;
    
    if (!load_mel_filters(mel_filters_path)) {
        std::cerr << "Failed to load mel filters" << std::endl;
        return ERR_MODEL_LOAD_FAILED;
    }
    
    if (!load_vocabulary(vocab_path)) {
        std::cerr << "Failed to load vocabulary" << std::endl;
        return ERR_MODEL_LOAD_FAILED;
    }
    
    ctx_ = new rknn_whisper_context_t();
    memset(ctx_, 0, sizeof(rknn_whisper_context_t));
    
    int ret = init_whisper_model(encoder_path.c_str(), &ctx_->encoder_context);
    if (ret != 0) {
        std::cerr << "Failed to init encoder" << std::endl;
        delete ctx_;
        ctx_ = nullptr;
        return ERR_MODEL_LOAD_FAILED;
    }
    
    ret = init_whisper_model(decoder_path.c_str(), &ctx_->decoder_context);
    if (ret != 0) {
        std::cerr << "Failed to init decoder" << std::endl;
        release_whisper_model(&ctx_->encoder_context);
        delete ctx_;
        ctx_ = nullptr;
        return ERR_MODEL_LOAD_FAILED;
    }
    
    initialized_ = true;
    std::cout << "Whisper models initialized" << std::endl;
    return ERR_SUCCESS;
}

ErrorCode WhisperHandler::transcribe(const std::vector<float>& pcm_data,
                                      const std::string& language,
                                      std::string& result) {
    if (!initialized_ || !ctx_) {
        return ERR_INTERNAL_ERROR;
    }
    
    int task_code = (language == "en") ? 50259 : 50260;
    std::vector<float> audio_data = pcm_data;
    
    if (audio_data.size() > MAX_AUDIO_LENGTH) {
        audio_data.resize(MAX_AUDIO_LENGTH);
    }
    
    std::vector<float> x_mel(N_MELS * MAX_AUDIO_LENGTH / HOP_LENGTH, 0.0f);
    
    audio_buffer_t audio;
    memset(&audio, 0, sizeof(audio_buffer_t));
    audio.data = (float*)malloc(audio_data.size() * sizeof(float));
    memcpy(audio.data, audio_data.data(), audio_data.size() * sizeof(float));
    audio.num_frames = audio_data.size();
    audio.num_channels = 1;
    audio.sample_rate = SAMPLE_RATE;
    
    audio_preprocess(&audio, mel_filters_.data(), x_mel);
    
    std::vector<std::string> recognized_text;
    int ret = inference_whisper_model(ctx_, x_mel, mel_filters_.data(), 
                                       vocab_.data(), task_code, recognized_text);
    
    if (audio.data) {
        free(audio.data);
    }
    
    if (ret != 0) {
        std::cerr << "Inference failed" << std::endl;
        return ERR_INFERENCE_FAILED;
    }
    
    result.clear();
    for (const auto& text : recognized_text) {
        result += text;
    }
    
    return ERR_SUCCESS;
}

bool WhisperHandler::load_vocabulary(const std::string& path) {
    return (read_vocab(path.c_str(), vocab_.data()) == 0);
}

bool WhisperHandler::load_mel_filters(const std::string& path) {
    return (read_mel_filters(path.c_str(), mel_filters_.data(), 
                              N_MELS * MELS_FILTERS_SIZE) == 0);
}

std::string WhisperHandler::get_status() const {
    return initialized_ ? "initialized" : "not initialized";
}
