//
// Created by gabor.nemeth on 12/1/22.
//

#ifndef HF_02_PROGRAM_H
#define HF_02_PROGRAM_H


#include <string>

#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"


class Program {
private:
    std::string _input_path;
    std::string _output_path = "output.txt";

    int _from_console;
    int _from_file;

    int parse_args(int argc, const char* argv[]);
    bool validate_args();
public:
    void run(int argc, const char* argv[]);
};


#endif //HF_02_PROGRAM_H
