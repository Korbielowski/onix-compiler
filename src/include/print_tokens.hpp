#include "tokenizer.hpp"

#include <vector>
// ? Should iostream also be included here or only in tokenizer.hpp, from where
// iostream is imported to this file #include <iostream>

// ? Don't know where this operator overload should be located, here or in
// tokenizer.hpp and tokenizer.cpp file
inline std::ostream &
operator<<(std::ostream &out_stream, const Token &token) {
    std::string token_value = token.value.has_value() ? token.value.value() : "\0";
    std::string token_name;
    switch (token.type) {
    case TokenType::TOKEN_VAR_IDENT:
        token_name = "variable identifier";
        break;
    case TokenType::TOKEN_IDENT_INT:
        token_name = "int identifier";
        break;
    case TokenType::TOKEN_IDENT_DOUBLE:
        token_name = "double identifier";
        break;
    case TokenType::TOKEN_IDENT_STRING:
        token_name = "string identifier";
        break;
    case TokenType::TOKEN_IDENT_BOOLEAN:
        token_name = "boolean identifier";
        break;
    case TokenType::TOKEN_INT:
        token_name = "int literal";
        break;
    case TokenType::TOKEN_DOUBLE:
        token_name = "double literal";
        break;
    case TokenType::TOKEN_STRING:
        token_name = "string literal";
        break;
    case TokenType::TOKEN_BOOLEAN:
        token_name = "boolean literal";
        break;
    case TokenType::TOKEN_DOT:
        token_name = "Dot .";
        break;
    case TokenType::TOKEN_SEMI:
        token_name = "semicolon ;";
        break;
    case TokenType::TOKEN_COMMA:
        token_name = "comma ,";
        break;
    case TokenType::TOKEN_QUOTE:
        token_name = "quote ";
        break;
    case TokenType::TOKEN_OPENPAR:
        token_name = "opening parenthesis (";
        break;
    case TokenType::TOKEN_CLOSEPAR:
        token_name = "closing parenthesis )";
        break;
    case TokenType::TOKEN_IF:
        token_name = "if";
        break;
    case TokenType::TOKEN_ELIF:
        token_name = "elif";
        break;
    case TokenType::TOKEN_ELSE:
        token_name = "else";
        break;
    case TokenType::TOKEN_RETURN:
        token_name = "return";
        break;
    case TokenType::TOKEN_FUNC:
        token_name = "func";
        break;
    case TokenType::TOKEN_FOR:
        token_name = "for";
        break;
    case TokenType::TOKEN_WHILE:
        token_name = "while";
        break;
    case TokenType::TOKEN_EQUAL:
        token_name = "equal =";
        break;
    default:
        token_name = "no token found";
        break;
    }
    out_stream << token_name << "\t" << token_value << "\n";
    return out_stream;
}

void print_tokens(const std::vector<Token> &tokens);
void print_token(const Token &token);