#include "include/tokenization.hpp"
#include "include/ansi_colors.hpp"
#include "include/generation.hpp"
#include "include/parser.hpp"

#include <iostream>
#include <optional>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *agrv[])
{
    if (argc < 2)
    {
        std::cerr << RED_TEXT << "ERROR\n"
                  << DEFAULT_TEXT
                  << "Too little arguments, minimum 2 arguments should be passed";
        return EXIT_FAILURE;
    }

    std::cout << "Reading data from the file\n";
    std::ifstream input(agrv[1]);
    std::stringstream contents_stream;
    contents_stream << input.rdbuf();
    input.close();
    std::string contents = contents_stream.str();

    std::cout << "Tokenizing string from the file\n";
    Tokenizer tokenizer(contents);
    std::vector<Token> tokens = tokenizer.tokenize();

    std::cout << "Parsing tokens into tree\n";
    Parser parser(std::move(tokens));
    std::optional<NodeExit> tree = parser.parse();

    if (!tree.has_value())
    {
        std::cerr << "No return statement found\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Generating code from parse tree\n";
    Generator generator(tree.value());

    std::ofstream output_file("output.asm");
    output_file << generator.generate();
    output_file.close();

    // system("nasm -felf64 output.asm");
    // system("ld output.o -o output");

    return EXIT_SUCCESS;
}