#include "include/tokenizer.hpp"

#include <iostream>

Tokenizer::Tokenizer(const std::string src) : m_source(std::move(src)) {}

std::vector<Token> Tokenizer::tokenize()
{
  std::vector<Token> tokens;
  std::string buffer;
  while (peek().has_value())
  {
    // Checks whether a letter
    if ((peek().value() >= 65 && peek().value() <= 90) ||
        (peek().value() >= 97 && peek().value() <= 122))
    {
      // Checks whether a letter or number
      while ((peek().value() >= 65 && peek().value() <= 90) ||
             (peek().value() >= 97 && peek().value() <= 122) ||
             (peek().value() >= 48 && peek().value() <= 57))
      {
        buffer.push_back(consume_char());
      }
      if (buffer == "int")
      {
        tokens.push_back({.type = TokenType::TOKEN_IDENT_INT});
        buffer.clear();
      }
      else if (buffer == "double")
      {
        tokens.push_back({.type = TokenType::TOKEN_IDENT_DOUBLE});
        buffer.clear();
      }
      else if (buffer == "string")
      {
        tokens.push_back({.type = TokenType::TOKEN_IDENT_STRING});
        buffer.clear();
      }
      else if (buffer == "boolean")
      {
        tokens.push_back({.type = TokenType::TOKEN_IDENT_BOOLEAN});
        buffer.clear();
      }
      else if (buffer == "return")
      {
        tokens.push_back({.type = TokenType::TOKEN_RETURN});
        buffer.clear();
      }
      else if (buffer == "if")
      {
        tokens.push_back({.type = TokenType::TOKEN_IF});
        buffer.clear();
      }
      else if (buffer == "elif")
      {
        tokens.push_back({.type = TokenType::TOKEN_ELIF});
        buffer.clear();
      }
      else if (buffer == "else")
      {
        consume_char();
        tokens.push_back({.type = TokenType::TOKEN_ELSE});
        buffer.clear();
      }
      else if (buffer == "while")
      {
        tokens.push_back({.type = TokenType::TOKEN_WHILE});
        buffer.clear();
      }
      else if (buffer == "for")
      {
        tokens.push_back({.type = TokenType::TOKEN_FOR});
        buffer.clear();
      }
      else if (buffer == "func")
      {
        tokens.push_back({.type = TokenType::TOKEN_FUNC});
        buffer.clear();
      }
      else
      {
        tokens.push_back({.type = TokenType::TOKEN_VAR_IDENT, .value = buffer});
        buffer.clear();
      }
    }
    // Checks whether a number
    else if (peek().value() >= 48 && peek().value() <= 57)
    {
      while (peek().value() != EOF && peek().value() >= 48 &&
             peek().value() <= 57)
      {
        buffer.push_back(consume_char());
      }
      tokens.push_back({.type = TokenType::TOKEN_INT, .value = buffer});
      buffer.clear();
    }
    else if (peek().value() == '=')
    {
      consume_char();
      tokens.push_back({.type = TokenType::TOKEN_EQUAL});
    }
    else if (peek().value() == ';')
    {
      consume_char();
      tokens.push_back({.type = TokenType::TOKEN_SEMI});
    }
    else if (peek().value() == ',')
    {
      consume_char();
      tokens.push_back({.type = TokenType::TOKEN_COMMA});
    }
    else if (peek().value() == '.')
    {
      consume_char();
      tokens.push_back({.type = TokenType::TOKEN_DOT});
    }
    else if (peek().value() == '(')
    {
      consume_char();
      tokens.push_back({.type = TokenType::TOKEN_OPENPAR});
    }
    else if (peek().value() == ')')
    {
      consume_char();
      tokens.push_back({.type = TokenType::TOKEN_CLOSEPAR});
    }
    else if (peek().value() == '"') // TODO! Add option for single quote
    {
      tokens.push_back({.type = TokenType::TOKEN_QUOTE});
    }
    else if (peek().value() == ' ' || peek().value() == '\n' ||
             peek().value() == '\t')
    {
      consume_char();
      continue;
    }
    else if (peek().value() == EOF)
    {
      break;
    }
  }
  m_index = 0;
  return tokens;
}
const std::optional<char> Tokenizer::peek(int offset) const
{
  if (m_index + offset >= m_source.length())
  {
    return EOF;
  }
  // std::cout << m_source.at(m_index);
  return m_source.at(m_index + offset);
}

char Tokenizer::consume_char() { return m_source.at(m_index++); }