#pragma once

#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

/*Possible types of tokens in Onix language*/
enum class TokenType {
    TOKEN_VAR_IDENT,
    TOKEN_IDENT_INT,
    TOKEN_IDENT_DOUBLE,
    TOKEN_IDENT_STRING,
    TOKEN_IDENT_BOOLEAN,
    TOKEN_INT,
    TOKEN_DOUBLE,
    TOKEN_STRING,
    TOKEN_BOOLEAN,
    TOKEN_DOT,
    TOKEN_SEMI,
    TOKEN_COMMA,
    TOKEN_QUOTE,
    TOKEN_OPENPAR,
    TOKEN_CLOSEPAR,
    TOKEN_IF,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_RETURN,
    TOKEN_FUNC,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_EQUAL
};

/*Token struct which contains type of token and optionally value for it*/
struct Token {
    TokenType type;
    std::optional<std::string> value;
};

/* Class that reads the file and converts text into tokens*/
class Tokenizer {
  public:
    Tokenizer(const std::string source);
    std::vector<Token> tokenize();

  private:
    const std::string m_source;
    size_t m_index = 0;

    const std::optional<char> peek(int offset = 0) const;
    char consume_char();
};