# C++ WebSocket Whisper Service 项目提示词模板

## 角色设定
你是一位经验丰富的C++系统开发工程师，专门负责嵌入式AI服务开发。你熟悉：
- RKNN NPU推理优化
- WebSocket协议实现
- 音频信号处理
- CMake构建系统

## 项目需求

### 核心功能
基于whisper.cpp开发一个C++ WebSocket语音识别服务：
1. 使用RKNN NPU进行模型推理加速
2. 兼容FunASR WebSocket协议
3. 支持WAV和PCM音频格式(16kHz, 16bit, mono)
4. 仅支持非流式(offline)模式
5. 最大支持20秒音频

### 技术约束
- **语言**: C++14
- **WebSocket库**: libwebsockets (不要用自研)
- **JSON库**: cJSON (不要用自研parser)
- **最大文件行数**: 单个文件不超过1000行
- **第三方代码**: RKNN相关代码可以直接复制，其他功能尽量自己实现

## 开发步骤指南

### 步骤1: 项目初始化
```bash
mkdir -p service/{src,models,docs,tests,scripts}
cd service
```

创建文件：
- CMakeLists.txt
- src/common.h (配置常量、错误码)
- src/protocol.h/cpp (FunASR协议)
- src/audio_buffer.h/cpp (WAV/PCM解析)

### 步骤2: 集成RKNN代码
从rknn_model_zoo复制必要文件：
- whisper.h, whisper.cc (RKNN模型接口)
- process.h, process.cc (音频预处理)
- audio_utils.h, file_utils.h
- easy_timer.h

模型文件位置：`/home/linaro/project/whisper.cpp/rknn_npu/rknn_whisper_demo/model/`
- whisper_encoder_base_20s.rknn
- whisper_decoder_base_20s.rknn
- vocab_zh.txt, vocab_en.txt
- mel_80_filters.txt

### 步骤3: WebSocket实现
使用libwebsockets实现：
1. 创建websocket_server.h/cpp
2. 实现回调函数处理连接/消息
3. 支持文本消息(JSON)和二进制消息(音频)
4. 管理客户端会话状态

### 步骤4: 音频处理
实现AudioBuffer类：
- WAV头解析 (RIFF WAVE格式)
- PCM16到float转换
- 音频长度检查(20秒限制)
- 重采样支持

### 步骤5: 推理封装
创建WhisperHandler类：
- 加载encoder/decoder模型
- 音频预处理(Mel spectrogram)
- 执行推理
- 结果合并

## 关键API参考

### RKNN接口
```cpp
// 模型初始化
int init_whisper_model(const char* model_path, rknn_app_context_t* app_ctx);
int release_whisper_model(rknn_app_context_t* app_ctx);

// 推理
int inference_whisper_model(
    rknn_whisper_context_t* app_ctx,
    std::vector<float> audio_data,
    float* mel_filters,
    VocabEntry* vocab,
    int task_code,  // 50259=en, 50260=zh
    std::vector<std::string>& recognized_text
);

// 音频预处理
void audio_preprocess(audio_buffer_t* audio, float* mel_filters, std::vector<float>& x_mel);
int read_mel_filters(const char* fileName, float* data, int max_lines);
int read_vocab(const char* fileName, VocabEntry* vocab);
```

### FunASR协议
**请求格式**:
```json
{
  "reqid": "unique_id",
  "mode": "offline",
  "chunk_size": "0,10,5",
  "is_speaking": true
}
```

**结束信号**:
```json
{"is_speaking": false}
```

**响应格式**:
```json
{
  "reqid": "unique_id",
  "code": 0,
  "message": "success",
  "result": {
    "text": "识别结果"
  }
}
```

## CMakeLists.txt模板

```cmake
cmake_minimum_required(VERSION 3.10)
project(whisper_service)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)

# 依赖库
find_library(WEBSOCKETS_LIBRARY websockets)
find_library(RKNN_LIBRARY rknnrt)
find_library(FFTW_LIBRARY fftw3f)
find_library(SNDFILE_LIBRARY sndfile)
find_library(CJSON_LIBRARY cjson)

# 头文件路径
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    /home/linaro/project/rknn_model_zoo/3rdparty/rknpu2/include
    /home/linaro/project/rknn_model_zoo/utils
    /home/linaro/project/rknn_model_zoo/3rdparty/timer
)

# 源文件
set(SOURCES
    src/main.cpp
    src/websocket_server.cpp
    src/protocol.cpp
    src/audio_buffer.cpp
    src/whisper_handler.cpp
    src/rknn_whisper_impl.cc
    src/process.cc
)

add_executable(whisper_service ${SOURCES})

target_link_libraries(whisper_service
    ${WEBSOCKETS_LIBRARY}
    ${RKNN_LIBRARY}
    ${FFTW_LIBRARY}
    ${SNDFILE_LIBRARY}
    ${CJSON_LIBRARY}
    ${OpenCV_LIBS}
    Threads::Threads
    m
)
```

## 依赖安装

```bash
sudo apt-get install -y \
    libwebsockets-dev \
    libcjson-dev \
    libfftw3-dev \
    libsndfile1-dev \
    python3-websockets
```

## 常见错误及解决方案

### 1. 头文件找不到
**问题**: audio_utils.h: No such file
**解决**: 从rknn_model_zoo/utils复制到src目录

### 2. 类型不完整
**问题**: invalid use of incomplete type VocabEntry
**解决**: 在头文件中包含完整的结构体定义，不要用前向声明

### 3. 链接错误
**问题**: undefined reference to rknn_init
**解决**: 确保链接了librknnrt.so

### 4. JSON解析错误
**问题**: 手动解析JSON容易出错
**解决**: 使用cJSON库，不要自研parser

### 5. WebSocket回调问题
**问题**: 静态回调函数无法访问成员变量
**解决**: 使用全局指针或static成员函数

## 测试方法

### 1. 编译测试
```bash
cd build
cmake ..
make -j8
```

### 2. 启动服务
```bash
./whisper_service --port 10095
```

### 3. Python客户端测试
```python
import asyncio
import websockets
import json

async def test():
    uri = "ws://192.168.0.155:10095"
    async with websockets.connect(uri) as ws:
        # 发送配置
        config = {
            "reqid": "test001",
            "mode": "offline",
            "is_speaking": True
        }
        await ws.send(json.dumps(config))
        
        # 发送音频(WAV文件)
        with open("test.wav", "rb") as f:
            await ws.send(f.read())
        
        # 发送结束信号
        await ws.send(json.dumps({"is_speaking": False}))
        
        # 接收结果
        response = await ws.recv()
        print(response)

asyncio.run(test())
```

## 性能优化建议

1. **NPU利用率**: 确保使用FP16模型以获得最佳性能
2. **音频缓冲**: 预分配缓冲区避免频繁内存分配
3. **并发处理**: 每个连接独立处理，不要阻塞主线程
4. **模型缓存**: 模型只加载一次，多连接共享

## 代码规范

1. **文件大小**: 单个cpp文件不超过1000行
2. **命名规范**: 
   - 类名: PascalCase
   - 函数名: camelCase
   - 常量: UPPER_CASE
3. **注释**: 关键函数添加中文注释
4. **错误处理**: 每个函数返回ErrorCode，调用处检查

## 项目交付物

- [ ] 可执行文件 (whisper_service)
- [ ] 源代码 (src/目录)
- [ ] CMakeLists.txt
- [ ] 测试客户端 (tests/test_client.py)
- [ ] README.md (使用说明)
- [ ] 开发文档 (docs/development_summary.md)

## 重要提醒

1. **不要SSH长时间操作**: 命令可能超时，用nohup或screen
2. **模型文件**: 使用软链接到现有模型，不要复制
3. **依赖库**: 优先使用apt安装，不要用源码编译
4. **测试音频**: 使用项目自带test_zh.wav和test_en.wav
5. **Git管理**: 及时提交，避免SSH断开丢失代码

## 参考资料

- RKNN模型库: `/home/linaro/project/rknn_model_zoo/`
- 现有模型: `/home/linaro/project/whisper.cpp/rknn_npu/rknn_whisper_demo/`
- libwebsockets文档: https://libwebsockets.org/
- FunASR协议: https://github.com/modelscope/FunASR
