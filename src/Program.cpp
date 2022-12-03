//
// Created by gabor.nemeth on 12/1/22.
//

#include "Program.h"
#include "ExpressionReader.h"

void Program::run(int argc, const char* argv[]) {
    parse_args(argc, argv);

    if (!validate_args())
        return;

    std::shared_ptr<Expression> expression;
    if (_from_console) {
        std::cout << "Console is active! Please insert expression line-by-line using Reverse Polish Notation! Expression is ended in case of empty line!" << std::endl;
        expression = ExpressionReader::from_istream(std::cin);
    }

    if (_from_file) {
        std::ifstream ifile(_input_path);
        expression = ExpressionReader::from_istream(ifile);
    }

    std::cout << expression->evaluate(BigNum{0}) << std::endl;
}

int Program::parse_args(int argc, const char* argv[]) {
    CLI::App app{"BigNum: Basic arithmetic operations using arbitrary-sized integers using Reverse Polish notation.\nCurrently accepting input from console or from file.\n\n"
                 "To read from console use: ./bigint -c\n"
                 "To read from file use: ./bigint -f -i <input_path> -o <output_path>\n"};

    app.add_flag("-c,--from-console", _from_console, "Read from console.");
    app.add_flag("-f,--from-file", _from_file, "Read from file. Requires --input <input> option.");
    app.add_option("-i,--input", _input_path, "File path to input text file.");
    app.add_option("-o,--output", _output_path, "File path to output text file.");

    CLI11_PARSE(app, argc, argv);
    return 0;
}

bool Program::validate_args() {
    if (_from_console != 0 && _from_file != 0) {
        std::cout << "Error: The program should be used with either -c or -f flag! Both were given." << std::endl << "Exiting." << std::endl;
        return false;
    }

    if (_from_console == 0 && _from_file == 0) {
        std::cout << "Error: The program should be used with either -c or -f flag! None were given." << std::endl << "Exiting." << std::endl;
        return false;
    }

    if (_from_console != 0)
        return true;

    if (_input_path.empty()) {
        std::cout << "Error: No input path was provided." << std::endl << "Exiting." << std::endl;
        return false;
    }

    if (_output_path.empty()) {
        std::cout << "Warning: No output path was provided. Defaulting to output.txt" << std::endl;
    }

    if (_input_path.find("txt") == std::string::npos) {
        std::cout << "Error: Input path is not a txt file. Exiting." << std::endl;
        return false;
    }

    if (_output_path.find("txt") == std::string::npos) {
        std::cout << "Warning: Output path is not a txt file. Defaulting to output.txt" << std::endl;
        _output_path = "output.txt";
    }

    return true;
}
