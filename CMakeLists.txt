# the whole CMakeLists.txt for project face_mask
PROJECT(face_mask)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_COMPILE_OPTIONS(-std=c++11)

# usage:cmake -DCMAKE_BUILD_TYPE=Release ..
#       cmake -DCMAKE_BUILD_TYPE=Debug ..
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g3 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")

# include directories
INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/thirdpart/include
        ${PROJECT_SOURCE_DIR}/thirdpart/include/openblas/include
        ${PROJECT_SOURCE_DIR}/lib/include
        /usr/local/cuda-9.0/include
)

# lib directories
LINK_DIRECTORIES(
        ${PROJECT_BINARY_DIR}/lib
)

# output directories
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(test)
