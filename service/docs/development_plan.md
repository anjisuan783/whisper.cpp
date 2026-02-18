# Whisper RKNN WebSocket Service - 开发计划与进度

## 项目概述
基于whisper.cpp和RKNN NPU加速的WebSocket语音识别服务，兼容FunASR协议。
部署在RK3576平台，使用6 TOPS NPU硬件加速。

## 技术栈
- **编程语言**: C++14
- **WebSocket库**: libwebsockets 4.1.6
- **AI推理**: RKNN Runtime (NPU加速)
- **音频处理**: FFTW3, libsndfile
- **JSON解析**: cJSON
- **构建工具**: CMake 3.10+

## 开发进度

### 阶段1: 项目初始化 (已完成)
- [x] 创建项目目录结构 (service/{src,models,docs,tests})
- [x] 创建CMakeLists.txt构建配置
- [x] 复制RKNN模型库文件到models/目录
- [x] 创建模型软链接 (whisper_encoder/decoder_base_20s.rknn)

### 阶段2: 核心模块开发 (已完成)
- [x] common.h - 通用定义、配置常量、错误码
- [x] protocol.h/cpp - FunASR协议实现 (使用cJSON)
- [x] audio_buffer.h/cpp - 音频缓冲区 (支持WAV/PCM格式)
- [x] whisper_handler.h/cpp - RKNN推理封装
- [x] websocket_server.h/cpp - WebSocket服务器 (libwebsockets)
- [x] main.cpp - 服务入口

### 阶段3: 依赖安装 (已完成)
- [x] libwebsockets-dev
- [x] libcjson-dev
- [x] libfftw3-dev
- [x] libsndfile1-dev
- [x] librknnrt (已预装)

### 阶段4: 编译 (已完成)
- [x] CMake配置成功
- [x] 编译通过 (whisper_service 215KB)

### 阶段5: 测试验证 (已完成)
- [x] 服务启动测试 (端口10095)
- [x] 模型加载测试 (encoder/decoder初始化成功)
- [x] 端到端测试 (FunASR协议客户端)
- [x] 中文语音识别测试成功

## 测试结果

### 服务启动


### 识别测试
**输入**: test_zh.wav (中文测试音频)
**输出**: 


## 项目文件清单

### 源代码 (src/)
- main.cpp - 入口点
- common.h - 通用定义
- protocol.h/cpp - FunASR协议 (使用cJSON)
- audio_buffer.h/cpp - 音频处理
- whisper_handler.h/cpp - RKNN推理封装
- websocket_server.h/cpp - WebSocket服务器
- 第三方代码:
  - whisper.h, whisper.cc (RKNN模型接口)
  - process.h, process.cc (音频预处理)
  - audio_utils.h, file_utils.h, easy_timer.h (工具库)

### 模型文件 (models/)
- whisper_encoder_base_20s.rknn (50MB)
- whisper_decoder_base_20s.rknn (163MB)
- vocab_zh.txt, vocab_en.txt
- mel_80_filters.txt

### 构建文件
- CMakeLists.txt
- build/whisper_service (可执行文件)

### 测试文件 (tests/)
- test_client.py - Python测试客户端

### 文档 (docs/)
- development_plan.md (本文件)
- README.md

## 使用说明

### 启动服务


### 测试客户端


## 后续优化建议
1. 支持长音频分块处理 (>20秒)
2. 添加更多错误处理
3. 实现并发请求支持
4. 添加性能监控
5. 支持更多音频格式
