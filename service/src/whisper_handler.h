#ifndef WHISPER_HANDLER_H
#define WHISPER_HANDLER_H

#include <string>
#include <vector>
#include <memory>
#include "common.h"
#include "whisper.h"
#include "process.h"

class WhisperHandler {
public:
    WhisperHandler();
    ~WhisperHandler();
    
    ErrorCode initialize(const std::string& encoder_path,
                         const std::string& decoder_path,
                         const std::string& vocab_path,
                         const std::string& mel_filters_path);
    
    ErrorCode transcribe(const std::vector<float>& pcm_data,
                         const std::string& language,
                         std::string& result);
    
    bool is_initialized() const { return initialized_; }
    std::string get_status() const;
    
private:
    bool initialized_;
    rknn_whisper_context_t* ctx_;
    std::vector<VocabEntry> vocab_;
    std::vector<float> mel_filters_;
    std::string vocab_path_;
    std::string mel_filters_path_;
    
    bool load_vocabulary(const std::string& path);
    bool load_mel_filters(const std::string& path);
};

#endif
