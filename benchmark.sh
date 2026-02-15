#!/bin/bash
MODEL="models/ggml-base-q8_0.bin"
TEST_DIR="test_audio"
THREADS=8

echo "======================================"
echo "Whisper.cpp 性能测试 - RK3576"
echo "模型: base-q8_0 (INT8)"
echo "线程: $THREADS"
echo "时间: $(date)"
echo "======================================"
echo ""

for audio in $TEST_DIR/*_16k.wav; do
    filename=$(basename "$audio")
    echo "测试: $filename"
    
    # 测试性能和转录
    /usr/bin/time -f "Elapsed: %E\nMax memory: %M KB\nCPU: %P" ./build/bin/whisper-cli         -m "$MODEL"         -f "$audio"         --threads $THREADS         -l zh         -otxt         -of "/tmp/result_${filename%.wav}"         2>&1 | grep -E '(Elapsed|Max memory|CPU|%|test)'
    
    echo "---"
done

echo ""
echo "======================================"
echo "测试完成"
echo "======================================"
