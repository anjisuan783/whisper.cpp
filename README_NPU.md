# RK3576 NPU 优化分支 (npu)

## 分支说明

本分支用于实施 RK3576 NPU 加速优化计划，目标是通过 6 TOPS NPU 提升 Whisper 语音识别性能。

## 当前状态

- **基线性能**: NEON 版本 2.2x 实时率
- **目标性能**: NPU 加速 4-5x 实时率
- **策略**: NPU Encoder + CPU Decoder 混合架构

## 目录结构



## 实施计划

### 阶段 1: 环境准备 (Day 1)
- [ ] 安装 RKNN Toolkit Lite2
- [ ] 克隆 rknn_model_zoo
- [ ] 配置 NPU 运行时环境

### 阶段 2: 模型获取 (Day 2)
- [ ] 下载预转换的 Whisper RKNN 模型
- [ ] 验证模型完整性

### 阶段 3: 编译和测试 (Day 3-4)
- [ ] 编译 RKNN C API 示例
- [ ] 使用测试音频验证性能
- [ ] 对比 NEON vs NPU 结果

### 阶段 4: 优化和集成 (Day 5-7)
- [ ] 性能调优
- [ ] 错误处理和边界情况
- [ ] 文档编写

## 快速开始

### 1. 环境准备
```bash
cd rknn_npu/scripts
bash setup_env.sh
```

### 2. 获取模型
```bash
cd rknn_npu/models
bash download_models.sh
```

### 3. 编译
```bash
cd rknn_npu/src
bash build.sh
```

### 4. 测试
```bash
cd rknn_npu/test
bash benchmark_rknn.sh
```

## 风险评估

- **高风险**: Decoder 可能无法完全转为 RKNN
- **中风险**: 20秒音频长度限制
- **低风险**: Encoder 转换成功率 > 90%

## 退出条件

- 如果 NPU 版本 < 3x 实时率 → 放弃，保持 NEON 版本
- 如果 Decoder 完全无法转换 → 采用 Encoder-only 方案

## 参考文档

- [NPU 优化详细计划](rknn_npu/docs/NPU_PLAN.md)
- [RKNN Model Zoo](https://github.com/airockchip/rknn_model_zoo)
- [Radxa Whisper 文档](https://docs.radxa.com/en/rock5/rock5b/app-development/ai/whisper)

## 分支作者

- 创建时间: 2026-02-16
- 目标平台: RK3576 @ 192.168.50.225
- 基线分支: master

