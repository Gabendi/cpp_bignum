# **BigNum for c++**

This is the second homework assignment for C++11 Programming lectures at BME.

# Installation



##  Local install
Run the following commands:

    git clone [https://github.com/Gabendi/cpp_bignum.git](https://github.com/Gabendi/cpp_bignum.git) && cd cpp_bignum \
    mkdir thirdparty && cd thirdparty \
    git clone [https://github.com/CLIUtils/CLI11.git](https://github.com/CLIUtils/CLI11.git) && cd .. \
    mkdir build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./build \
    cd build && cmake --build . --target hf_02 -j 6

## Using docker

Simply use the profided Dockerfile to build the image:

    docker build -t cpp_bignum:latest .

# Usage
## Locally
As easy as it gets, run:

    ./bignum -c
or read from file by

    ./bignum -f --input ../example/example.txt


## Using docker
Just simply start the program in console by running the following command:

    docker run --rm -it cpp_bignum:latest bignum -c
   
or alternatively  you can read from a file e.g.: the file in the example

    docker run --rm -v ~/cpp_bignum/example:/home -it cpp_bignum:latest bignum -f --input /home/example.txt

## Delete a file

You can delete the current file by clicking the **Remove** button in the file explorer. The file will be moved into the **Trash** folder and automatically deleted after 7 days of inactivity.

# Parameters

 - -c: Read from console.
 - -f: Read from file. Requires --input <input_path> option provided.
 - -i, --input: File path to input txt file.
 - --help: Invoke for more instructions.
 
