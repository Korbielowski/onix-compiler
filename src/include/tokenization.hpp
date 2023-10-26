#pragma once

#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

// Types of possible tokens of Onix language
enum class TokenType
{
    TOKEN_INT,
    TOKEN_DOUBLE,
    TOKEN_STRING,
    TOKEN_BOOLEAN,
    TOKEN_DOT,
    TOKEN_SEMI,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_OPENPAR,
    TOKEN_CLOSEPAR,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_ELIF,
    TOKEN_RETURN,
    TOKEN_FUNC,
    TOKEN_FOR,
    TOKEN_WHILE
};

struct Token
{
    TokenType type;
    std::optional<std::string> value;
};

// Class for converting text from file into tokens
class Tokenizer
{
public:
    Tokenizer(const std::string source);
    std::vector<Token> tokenize();

private:
    const std::string m_source;
    size_t m_index = 0;

    const std::optional<char> peek(int offset = 0) const;
    char consume();
};