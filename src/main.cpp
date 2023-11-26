#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "include/ansi_colors.hpp"
#include "include/generator.hpp"
#include "include/parser.hpp"
#include "include/print_tokens.hpp"
#include "include/tokenizer.hpp"

int
main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << RED_TEXT << "ERROR\n"
                  << DEFAULT_TEXT << "Too little arguments, minimum 2 arguments should be passed";
        return EXIT_FAILURE;
    }

    std::cout << "Reading data from the file\n";
    std::ifstream input(argv[1]);
    std::stringstream contents_stream;
    contents_stream << input.rdbuf();
    input.close();
    std::string contents = contents_stream.str();

    std::cout << "Tokenizing strings from the file\n";
    Tokenizer tokenizer(contents);
    std::vector<Token> tokens = tokenizer.tokenize();
    print_tokens(tokens);

    std::cout << "Parsing tokens into tree\n";
    Parser parser(std::move(tokens));
    std::optional<NodeProg> tree = parser.parse_prog();

    if (!tree.has_value()) {
        std::cerr << "Invalid program\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Generating code from parse tree\n";
    Generator generator(tree.value());

    std::cout << "Writing to .asm file\n";
    std::ofstream output_file("output.asm");
    output_file << generator.generate_prog();
    output_file.close();

    if (std::string(argv[1]) == "-f" || std::string(argv[1]) == "--fast") {
        std::cout << "\nleaea\n";
        system("nasm -felf64 output.asm");
        system("ld output.o -o output");
        std::cout << "Program has been compiled and is trying to be run" << std::endl;
        system("./output || echo $?");
    } else if (std::string(argv[1]) == "-d" || std::string(argv[1]) == "--debug") {
        std::cout << "Compiling program in debug mode" << std::endl;
        system("nasm -felf64 output.asm");
        system("ld output.o -o output");
        std::cout << "Program has been compiled" << std::endl;
    } else {
        system("nasm -felf64 output.asm");
        system("ld output.o -o output");
        std::cout << "Program has been compiled" << std::endl;
    }
    return EXIT_SUCCESS;
}