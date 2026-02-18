#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <map>
#include "common.h"

struct FunasrMessage {
    std::string reqid;
    std::string mode;
    std::string chunk_size;
    int encoder_chunk_look_back;
    int decoder_chunk_look_back;
    int chunk_interval;
    bool is_speaking;
    std::string wav_name;
    std::string audio_format;
    int audio_fs;
    std::map<std::string, std::string> raw_fields;
    
    FunasrMessage() : encoder_chunk_look_back(4), decoder_chunk_look_back(0), 
                      chunk_interval(10), is_speaking(true), audio_fs(16000) {}
};

bool parse_funasr_config(const std::string& json_str, FunasrMessage& msg, std::string& error);
std::string build_funasr_response(const std::string& reqid, ErrorCode code, const std::string& message, const std::string& text);
std::string build_error_response(const std::string& reqid, ErrorCode code, const std::string& details = std::string());
bool is_finish_message(const std::string& json_str);

#endif
