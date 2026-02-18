# Whisper RKNN WebSocket Service

基于whisper.cpp和RKNN NPU加速的WebSocket语音识别服务，兼容FunASR协议。

## 特性
- 使用RK3576 NPU硬件加速 (6 TOPS)
- 兼容FunASR WebSocket协议
- 支持WAV和PCM音频格式
- 支持中英文语音识别
- 最大支持20秒音频

## 编译



## 运行服务



参数:
- : WebSocket端口 (默认: 10095)
- : 模型目录 (默认: ./models)
- : 默认语言 zh/en (默认: zh)
- : 最大音频秒数 (默认: 20)

## FunASR协议

### 连接


### 请求格式

1. 发送配置 (JSON):


2. 发送音频数据 (二进制WAV或PCM)

3. 发送结束信号 (JSON):


### 响应格式


## 测试

使用Python客户端测试:

