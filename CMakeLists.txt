project(ALGORITHM-LEARN)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
include_directories(./include ./test)
add_definitions(-DDEBUG)        # 调试模式
aux_source_directory(./src SRC_LIB)
aux_source_directory(./test SRC_TEST)
add_executable(main main.cpp ${SRC_LIB} ${SRC_TEST})
