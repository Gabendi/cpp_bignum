cmake_minimum_required(VERSION 3.23)
project(hf_02)

set(CMAKE_CXX_STANDARD 20)

if(NOT DEFINED CLI11_DIR)
    set (CLI11_DIR "thirdparty/CLI11" CACHE STRING "CLI11 git repository")
endif()

include_directories(${CLI11_DIR}/include)
include_directories(include)

add_executable(hf_02 src/main.cpp src/Program.cpp include/Program.h src/ExpressionReader.cpp include/ExpressionReader.h include/expression.h src/BigNum.cpp include/BigNum.h)

