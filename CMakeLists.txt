cmake_minimum_required(VERSION 3.16)
project(bignum)

set(CMAKE_CXX_STANDARD 20)

if (NOT DEFINED CLI11_DIR)
    set(CLI11_DIR "thirdparty/CLI11" CACHE STRING "CLI11 git repository")
endif ()

include_directories(${CLI11_DIR}/include)
include_directories(include)

add_executable(bignum src/main.cpp src/Program.cpp include/Program.h src/ExpressionReader.cpp include/ExpressionReader.h include/expression.h src/BigNum.cpp include/BigNum.h)

