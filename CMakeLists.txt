cmake_minimum_required(VERSION 3.20)

project(onix)

set(CMAKE_CXX_STANDARD 20)

add_executable(onix ./src/main.cpp ./src/tokenizer.cpp ./src/parser.cpp ./src/generator.cpp ./src/print_tokens.cpp)