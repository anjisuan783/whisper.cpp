#include "audio_buffer.h"
#include <cstring>
#include <algorithm>

AudioBuffer::AudioBuffer() {}

AudioBuffer::~AudioBuffer() {}

void AudioBuffer::reset() {
    buffer_.clear();
}

void AudioBuffer::append(const uint8_t* data, size_t len) {
    if (data && len > 0) {
        buffer_.insert(buffer_.end(), data, data + len);
    }
}

AudioFormat AudioBuffer::detect_format() const {
    if (buffer_.size() < 12) {
        return AUDIO_FORMAT_UNKNOWN;
    }
    if (buffer_[0] == 'R' && buffer_[1] == 'I' && 
        buffer_[2] == 'F' && buffer_[3] == 'F' &&
        buffer_[8] == 'W' && buffer_[9] == 'A' &&
        buffer_[10] == 'V' && buffer_[11] == 'E') {
        return AUDIO_FORMAT_WAV;
    }
    return AUDIO_FORMAT_PCM;
}

bool AudioBuffer::has_complete_wav() const {
    if (buffer_.size() < 44) return false;
    const WavHeader* header = reinterpret_cast<const WavHeader*>(buffer_.data());
    if (memcmp(header->riff, "RIFF", 4) != 0 ||
        memcmp(header->wave, "WAVE", 4) != 0 ||
        memcmp(header->fmt, "fmt ", 4) != 0) {
        return false;
    }
    size_t offset = 36;
    while (offset + 8 <= buffer_.size()) {
        const char* chunk_id = reinterpret_cast<const char*>(buffer_.data() + offset);
        uint32_t chunk_size = *reinterpret_cast<const uint32_t*>(buffer_.data() + offset + 4);
        if (memcmp(chunk_id, "data", 4) == 0) {
            size_t total_size = offset + 8 + chunk_size;
            return buffer_.size() >= total_size;
        }
        offset += 8 + chunk_size;
        if (chunk_size % 2 != 0) offset++;
    }
    return false;
}

ErrorCode AudioBuffer::parse_wav(std::vector<float>& pcm_data, int& sample_rate) {
    pcm_data.clear();
    if (buffer_.size() < 44) return ERR_AUDIO_FORMAT_ERROR;
    const WavHeader* header = reinterpret_cast<const WavHeader*>(buffer_.data());
    if (memcmp(header->riff, "RIFF", 4) != 0 ||
        memcmp(header->wave, "WAVE", 4) != 0) {
        return ERR_AUDIO_FORMAT_ERROR;
    }
    sample_rate = header->sample_rate;
    uint16_t bits_per_sample = header->bits_per_sample;
    uint16_t num_channels = header->num_channels;
    size_t offset = 36;
    uint32_t data_size = 0;
    const uint8_t* data_ptr = nullptr;
    while (offset + 8 <= buffer_.size()) {
        const char* chunk_id = reinterpret_cast<const char*>(buffer_.data() + offset);
        uint32_t chunk_size = *reinterpret_cast<const uint32_t*>(buffer_.data() + offset + 4);
        if (memcmp(chunk_id, "data", 4) == 0) {
            data_size = chunk_size;
            data_ptr = buffer_.data() + offset + 8;
            break;
        }
        offset += 8 + chunk_size;
        if (chunk_size % 2 != 0) offset++;
    }
    if (!data_ptr || data_size == 0) return ERR_AUDIO_FORMAT_ERROR;
    size_t num_samples = data_size / (bits_per_sample / 8);
    if (bits_per_sample == 16) {
        const int16_t* samples = reinterpret_cast<const int16_t*>(data_ptr);
        if (num_channels == 1) {
            pcm_data.resize(num_samples);
            convert_pcm16_to_float(samples, pcm_data.data(), num_samples);
        } else if (num_channels == 2) {
            pcm_data.resize(num_samples / 2);
            for (size_t i = 0; i < num_samples / 2; i++) {
                float left = samples[2 * i] / 32768.0f;
                float right = samples[2 * i + 1] / 32768.0f;
                pcm_data[i] = (left + right) / 2.0f;
            }
        } else {
            return ERR_AUDIO_FORMAT_ERROR;
        }
    } else {
        return ERR_AUDIO_FORMAT_ERROR;
    }
    return ERR_SUCCESS;
}

ErrorCode AudioBuffer::get_pcm_data(std::vector<float>& pcm_data) {
    pcm_data.clear();
    if (buffer_.empty()) return ERR_AUDIO_FORMAT_ERROR;
    size_t num_samples = buffer_.size() / 2;
    pcm_data.resize(num_samples);
    const int16_t* samples = reinterpret_cast<const int16_t*>(buffer_.data());
    convert_pcm16_to_float(samples, pcm_data.data(), num_samples);
    return ERR_SUCCESS;
}

void AudioBuffer::convert_pcm16_to_float(const int16_t* pcm16, float* pcm_float, size_t num_samples) {
    for (size_t i = 0; i < num_samples; i++) {
        pcm_float[i] = pcm16[i] / 32768.0f;
    }
}
