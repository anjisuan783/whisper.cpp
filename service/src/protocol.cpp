#include "protocol.h"
#include "common.h"
#include <cjson/cJSON.h>
#include <sstream>

bool parse_funasr_config(const std::string& json_str, FunasrMessage& msg, std::string& error) {
    cJSON* root = cJSON_Parse(json_str.c_str());
    if (!root) {
        error = "invalid JSON";
        return false;
    }
    
    cJSON* item = cJSON_GetObjectItem(root, "reqid");
    if (item && cJSON_IsString(item)) msg.reqid = item->valuestring;
    
    item = cJSON_GetObjectItem(root, "mode");
    msg.mode = (item && cJSON_IsString(item)) ? item->valuestring : "offline";
    
    item = cJSON_GetObjectItem(root, "chunk_size");
    msg.chunk_size = (item && cJSON_IsString(item)) ? item->valuestring : "0,10,5";
    
    item = cJSON_GetObjectItem(root, "encoder_chunk_look_back");
    msg.encoder_chunk_look_back = (item && cJSON_IsNumber(item)) ? item->valueint : 4;
    
    item = cJSON_GetObjectItem(root, "decoder_chunk_look_back");
    msg.decoder_chunk_look_back = (item && cJSON_IsNumber(item)) ? item->valueint : 0;
    
    item = cJSON_GetObjectItem(root, "chunk_interval");
    msg.chunk_interval = (item && cJSON_IsNumber(item)) ? item->valueint : 10;
    
    item = cJSON_GetObjectItem(root, "is_speaking");
    msg.is_speaking = (item && cJSON_IsBool(item)) ? cJSON_IsTrue(item) : true;
    
    item = cJSON_GetObjectItem(root, "wav_name");
    if (item && cJSON_IsString(item)) msg.wav_name = item->valuestring;
    
    item = cJSON_GetObjectItem(root, "audio_format");
    msg.audio_format = (item && cJSON_IsString(item)) ? item->valuestring : "wav";
    
    item = cJSON_GetObjectItem(root, "audio_fs");
    msg.audio_fs = (item && cJSON_IsNumber(item)) ? item->valueint : 16000;
    
    cJSON_Delete(root);
    
    if (msg.mode != "offline") {
        error = "only offline mode supported";
        return false;
    }
    if (msg.reqid.empty()) {
        static int counter = 0;
        msg.reqid = "req_" + std::to_string(++counter);
    }
    return true;
}

std::string build_funasr_response(const std::string& reqid, ErrorCode code, const std::string& message, const std::string& text) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "text", text.c_str());
    cJSON_AddBoolToObject(root, "is_final", true);
    cJSON_AddStringToObject(root, "mode", "offline");
    
    char* str = cJSON_PrintUnformatted(root);
    std::string response(str);
    free(str);
    cJSON_Delete(root);
    return response;
}

std::string build_error_response(const std::string& reqid, ErrorCode code, const std::string& details) {
    std::string msg = get_error_message(code);
    if (!details.empty()) msg += std::string(": ") + details;
    return build_funasr_response(reqid, code, msg, "");
}

bool is_finish_message(const std::string& json_str) {
    cJSON* root = cJSON_Parse(json_str.c_str());
    if (!root) return false;
    
    cJSON* item = cJSON_GetObjectItem(root, "is_speaking");
    bool is_finish = (item && cJSON_IsBool(item) && !cJSON_IsTrue(item));
    
    cJSON_Delete(root);
    return is_finish;
}
