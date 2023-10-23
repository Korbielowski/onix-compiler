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
    if (argc != 2)
    {
        std::cerr << RED_TEXT << "ERROR\n"
                  << DEFAULT_TEXT
                  << "Too little arguments, minimum 2 arguments should be passed";
        return EXIT_FAILURE;
    }

    std::ifstream input(agrv[1]);
    std::stringstream contents_stream;
    contents_stream << input.rdbuf();
    input.close();
    std::string contents = contents_stream.str();

    Tokenizer tokenizer(contents);
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    std::optional<NodeExit> tree = parser.parse();

    if (!tree.has_value())
    {
        std::cerr << "No exit statement found\n";
        exit(EXIT_FAILURE);
    }

    Generator generator(tree.value());

    std::ofstream output_file("output.asm");
    output_file << generator.generate();
    output_file.close();

    // system("nasm -felf64 output.asm");
    // system("ld output.o -o output");

    return EXIT_SUCCESS;
}