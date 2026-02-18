#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include <vector>
#include <cstdint>
#include <string>
#include "common.h"

struct WavHeader {
    char riff[4];
    uint32_t file_size;
    char wave[4];
    char fmt[4];
    uint32_t fmt_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    char data[4];
    uint32_t data_size;
};

class AudioBuffer {
public:
    AudioBuffer();
    ~AudioBuffer();
    void reset();
    void append(const uint8_t* data, size_t len);
    AudioFormat detect_format() const;
    ErrorCode parse_wav(std::vector<float>& pcm_data, int& sample_rate);
    ErrorCode get_pcm_data(std::vector<float>& pcm_data);
    size_t size() const { return buffer_.size(); }
    const uint8_t* data() const { return buffer_.data(); }
    bool has_complete_wav() const;

private:
    std::vector<uint8_t> buffer_;
    void convert_pcm16_to_float(const int16_t* pcm16, float* pcm_float, size_t num_samples);
};

#endif
