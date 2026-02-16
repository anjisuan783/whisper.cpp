#!/bin/bash
# Extract RKNN models from split archives
# Usage: ./extract_models.sh

echo Extracting RKNN models...

if [ ! -f models_rknn.tar.gz.part.aa ] || [ ! -f models_rknn.tar.gz.part.ab ]; then
    echo Error: Model archive parts not found!
    echo Please ensure models_rknn.tar.gz.part.aa and models_rknn.tar.gz.part.ab exist.
    exit 1
fi

echo Combining split archives...
cat models_rknn.tar.gz.part.aa models_rknn.tar.gz.part.ab > models_rknn.tar.gz

echo Extracting models...
tar xzvf models_rknn.tar.gz

echo Cleaning up...
rm -f models_rknn.tar.gz

echo Done! Models extracted:
ls -lh *.rknn
