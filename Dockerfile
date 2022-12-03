FROM gcc:latest

WORKDIR /home

RUN set -ex;                                                                      \
    apt-get update;                                                               \
    apt-get install -y cmake libzmq3-dev;                                         \
    apt-get install -y ninja-build; \
    git clone https://github.com/Gabendi/cpp_bignum.git && \
    cd cpp_bignum && mkdir thirdparty && cd thirdparty &&\
    git clone https://github.com/CLIUtils/CLI11.git && cd .. &&\
    mkdir build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./build &&\
    cd build && cmake --build . --target hf_02 -j 6
    
RUN mv /home/cpp_bignum/build/hf_02 /usr/bin/bignum
