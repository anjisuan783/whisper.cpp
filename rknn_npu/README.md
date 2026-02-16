# RK3576 NPU Whisper Speech Recognition

## Overview

NPU-accelerated Whisper speech recognition on Rockchip RK3576 platform.

**Platform**: RK3576 (4xA72 + 4xA53, 6 TOPS NPU)  
**Host**: 192.168.0.155  
**Branch**: npu  
**Date**: 2026-02-16

---

## Performance Results

| Method | Real-time Factor | 20s Audio Time | Status |
|--------|------------------|----------------|--------|
| NEON (baseline) | 2.2x | 9.0s | Tested |
| **RKNN FP16** | **3.16x-3.46x** | **1.7-1.8s** | **Recommended** |
| RKNN INT8 | 4-5x (theory) | - | Not working |

**Performance Gain**: 44-57% faster than NEON

### Test Results

**Chinese** (test_zh.wav, 5.6s):
- Processing time: 1.775s
- RTF: 0.316 (3.16x)
- Output: 对我做了介绍...

**English** (test_en.wav, 5.9s):
- Processing time: 1.692s
- RTF: 0.289 (3.46x)
- Output: Mr. Quilter is the apostle...

---

## Quick Start

### 1. Extract Models



### 2. Run Inference



---

## File Structure



---

## Model Conversion

To convert ONNX to RKNN:



---

## Known Issues

### INT8 Quantization
- **Problem**: Produces empty or garbled output
- **Cause**: Whisper is sensitive to quantization
- **Status**: No stable solution, use FP16
- **Reference**: https://github.com/airockchip/rknn_model_zoo/issues/314

---

## References

- RKNN Model Zoo: https://github.com/airockchip/rknn_model_zoo
- RKNN Toolkit2: https://github.com/airockchip/rknn-toolkit2
- Whisper: OpenAI Whisper base model

---

## License

MIT License (same as whisper.cpp)
