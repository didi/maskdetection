# test directory CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
project(test)

ADD_COMPILE_OPTIONS(-std=c++11)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# lib directories
LINK_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/../build/lib
)

ADD_EXECUTABLE(mask main_face_mask.cpp)

TARGET_LINK_LIBRARIES(mask
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/caffe/libcaffe.so
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/opencv/libopencv_core.so
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/opencv/libopencv_highgui.so
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/opencv/libopencv_imgproc.so
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/opencv/libopencv_imgcodecs.so
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/opencv/libspeex.so.1
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/opencv/libnuma.so.1
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/cuda/libcublas.so
	${PROJECT_SOURCE_DIR}/../thirdpart/lib/cuda/libcudart.so
	${PROJECT_SOURCE_DIR}/../build/lib/libface_mask.so
	/usr/lib64/libboost_system.so
)
