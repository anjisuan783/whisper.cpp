# RK3576 NPU 优化实施进度

## 当前状态 (2026-02-16)

### ✅ 已完成

1. **环境准备**
   - 创建 Python 虚拟环境 (rknn_venv)
   - 安装 RKNN Toolkit Lite2
   - 验证 NPU 驱动 (/dev/rknpu 已加载)

2. **RKNN Model Zoo**
   - 克隆官方仓库
   - 下载 ONNX 模型 (Encoder 78MB + Decoder 299MB)
   - 成功编译 C++ 示例

3. **编译修复**
   - 安装系统 libfftw3-dev
   - 安装系统 libsndfile1-dev
   - 修改 CMakeLists.txt 使用系统库
   - 编译成功生成 rknn_whisper_demo

### ⚠️ 遇到的困难

1. **RKNN 模型获取**
   - 无法直接在 RK3576 上执行 ONNX → RKNN 转换
   - RKNN Toolkit2 安装超时/失败
   - 预转换模型下载困难 (404/访问限制)

2. **依赖问题**
   - 3rdparty 静态库未使用 -fPIC 编译
   - 已修复：改用系统动态库

### 📁 文件结构



### 🚀 使用说明

#### 运行演示 (需要 RKNN 模型)



### ⚠️ 缺少的资源

**必需的 RKNN 模型文件**:
-  (~20MB)
-  (~50MB)

**获取方式**:
1. **在 x86 PC 上转换** (推荐)
   

2. **寻找预转换模型**
   - Hugging Face: 搜索 whisper rk3576
   - RKNN Model Zoo Releases
   - 社区分享

3. **联系 Rockchip 支持**
   - GitHub Issues: airockchip/rknn_model_zoo
   - 官方论坛

### 📊 预期性能

一旦获得 RKNN 模型:
- **Encoder**: 3-5x 加速 (NPU)
- **Decoder**: 1x (CPU)
- **整体**: 从 2.2x → 4-5x 实时率

### 🔧 下一步建议

**方案 A: 完成 NPU 优化 (推荐)**
1. 在 x86 PC 上转换 ONNX → RKNN
2. 复制模型到 RK3576
3. 运行性能测试
4. 对比 NEON vs NPU 结果

**方案 B: 使用 ONNX Runtime**
1. 安装 onnxruntime-rknn
2. 直接使用现有的 ONNX 模型
3. 测试性能

**方案 C: 保持 NEON (当前)**
- 已有 2.2x 实时率
- 足够多数应用场景
- 稳定性好

### 📝 相关路径

- **工作目录**: 
- **编译好的 demo**: 
- **ONNX 模型**: 
- **Git 分支**: 

### 🔗 参考资源

- [RKNN Model Zoo](https://github.com/airockchip/rknn_model_zoo)
- [RKNN Toolkit2](https://github.com/airockchip/rknn-toolkit2)
- [Radxa Whisper 文档](https://docs.radxa.com/en/rock5/rock5b/app-development/ai/whisper)

### 👤 作者

- **实施**: AI Assistant
- **平台**: RK3576 @ 192.168.50.225
- **时间**: 2026-02-16
- **状态**: 等待 RKNN 模型

