cmake_minimum_required(VERSION 3.10)
project(whisper_service VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)

find_library(WEBSOCKETS_LIBRARY websockets PATHS /usr/lib /usr/local/lib)
find_path(WEBSOCKETS_INCLUDE_DIR libwebsockets.h PATHS /usr/include /usr/local/include)

if(NOT WEBSOCKETS_LIBRARY)
    message(FATAL_ERROR "libwebsockets not found")
endif()

find_library(RKNN_LIBRARY rknnrt PATHS /usr/lib /usr/local/lib /lib)

if(NOT RKNN_LIBRARY)
    message(FATAL_ERROR "librknnrt not found")
endif()

set(RKNN_INCLUDE_DIR /home/linaro/project/rknn_model_zoo/3rdparty/rknpu2/include)

find_library(FFTW_LIBRARY fftw3f PATHS /usr/lib /usr/local/lib)
find_path(FFTW_INCLUDE_DIR fftw3.h PATHS /usr/include)

find_library(SNDFILE_LIBRARY sndfile PATHS /usr/lib /usr/local/lib)
find_path(SNDFILE_INCLUDE_DIR sndfile.h PATHS /usr/include)

find_library(CJSON_LIBRARY cjson PATHS /usr/lib /usr/local/lib)
find_path(CJSON_INCLUDE_DIR cjson/cJSON.h PATHS /usr/include)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${WEBSOCKETS_INCLUDE_DIR}
    ${RKNN_INCLUDE_DIR}
    ${FFTW_INCLUDE_DIR}
    ${SNDFILE_INCLUDE_DIR}
    ${CJSON_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    /home/linaro/project/rknn_model_zoo/examples/whisper/cpp
    /home/linaro/project/rknn_model_zoo/utils
    /home/linaro/project/rknn_model_zoo/3rdparty/timer
)

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

install(TARGETS whisper_service DESTINATION bin)
