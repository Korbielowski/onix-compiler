#include "include/tokenization.hpp"

Tokenizer::Tokenizer(const std::string src)
    : m_source(std::move(src))
{
}

std::vector<Token> Tokenizer::tokenize()
{
    std::vector<Token> tokens;
    std::string buffer;
    while (peak().has_value())
    {
        if ((peak().value() >= 65 && peak().value() <= 90) || (peak().value() >= 97 && peak().value() <= 122))
        {
            while ((peak().value() >= 65 && peak().value() <= 90) || (peak().value() >= 97 && peak().value() <= 122) || (peak().value() >= 48 && peak().value() <= 57))
            {
                buffer.push_back(consume());
            }
            if (buffer == "return")
            {
                tokens.push_back(Token{TokenType::TOKEN_RETURN});
                // tokens.push_back({.type = TokenType::_return}); // Strange bug in VS Code. tokens.push_back(Token{TokenType::_return}); does not invoke an error
                buffer.clear();
            }
            else if (buffer == "if")
            {
                tokens.push_back(Token{TokenType::TOKEN_IF});
                buffer.clear();
            }
            else if (buffer == "else")
            {
                consume();
                tokens.push_back(Token{TokenType::TOKEN_ELSE});
                buffer.clear();
            }
            else if (buffer == "elif")
            {
                tokens.push_back(Token{TokenType::TOKEN_ELIF});
                buffer.clear();
            }
        }
        else if (peak().value() >= 48 && peak().value() <= 57)
        {
            buffer.push_back(consume());
            while (peak().value() >= 48 && peak().value() <= 57)
            {
                buffer.push_back(consume());
            }
            // tokens.push_back({.type = TokenType::int_lit, .value = buffer});
            tokens.push_back(Token{TokenType::TOKEN_INT, buffer});
            buffer.clear();
        }
        else if (peak().value() == ';')
        {
            consume();
            // tokens.push_back({.type = TokenType::semi});
            tokens.push_back(Token{TokenType::TOKEN_SEMI});
            // buffer.clear();
        }
        else if (peak().value() == ',')
        {
            consume();
            tokens.push_back(Token{TokenType::TOKEN_COLON});
        }
        else if (peak().value() == '.')
        {
            consume();
            tokens.push_back(Token{TokenType::TOKEN_DOT});
        }
        else if (peak().value() == '(')
        {
            consume();
            tokens.push_back(Token{TokenType::TOKEN_LEFTPAR});
        }
        else if (peak().value() == ')')
        {
            consume();
            tokens.push_back(Token{TokenType::TOKEN_RIGHTPAR});
        }
        else if (peak().value() == ' ')
        {
            consume();
            continue;
        }
    }

    // for (int i = 0; i < m_source.length(); i++)
    // {
    //     if ((m_source.at(i) >= 65 && m_source.at(i) <= 90) || (m_source.at(i) >= 97 && m_source.at(i) <= 122))
    //     {
    //         buffer.push_back(m_source.at(i));
    //         i++;
    //         while ((m_source.at(i) >= 65 && m_source.at(i) <= 90) || (m_source.at(i) >= 97 && m_source.at(i) <= 122) || (m_source.at(i) >= 48 && m_source.at(i) <= 57))
    //         {
    //             buffer.push_back(m_source.at(i));
    //             i++;
    //         }
    //         i--;
    //         if (buffer == "return")
    //         {
    //             // Token tok;
    //             // tok.type = TokenType::_return;
    //             // tokens.push_back(tok);
    //             tokens.push_back(Token{TokenType::TOKEN_RETURN});
    //             // tokens.push_back({.type = TokenType::_return}); // Strange bug in VS Code. tokens.push_back(Token{TokenType::_return}); does not invoke an error
    //             buffer.clear();
    //         }
    //         else if (buffer == "if")
    //         {
    //             tokens.push_back(Token{TokenType::TOKEN_IF});
    //             buffer.clear();
    //         }
    //         else if (buffer == "else")
    //         {
    //             tokens.push_back(Token{TokenType::TOKEN_ELSE});
    //             buffer.clear();
    //         }
    //         else if (buffer == "elif")
    //         {
    //             tokens.push_back(Token{TokenType::TOKEN_ELIF});
    //             buffer.clear();
    //         }
    //     }
    //     else if (m_source.at(i) >= 48 && m_source.at(i) <= 57)
    //     {
    //         buffer.push_back(m_source.at(i));
    //         i++;
    //         while (m_source.at(i) >= 48 && m_source.at(i) <= 57)
    //         {
    //             buffer.push_back(m_source.at(i));
    //             i++;
    //         }
    //         i--;
    //         // tokens.push_back({.type = TokenType::int_lit, .value = buffer});
    //         tokens.push_back(Token{TokenType::TOKEN_INT, buffer});
    //         buffer.clear();
    //     }
    // else if (m_source.at(i) == ';')
    // {
    //     // tokens.push_back({.type = TokenType::semi});
    //     tokens.push_back(Token{TokenType::TOKEN_SEMI});
    //     buffer.clear();
    // }
    // else if (m_source.at(i) == ',')
    // {
    //     // tokens.push_back({.type = TokenType::col});
    //     tokens.push_back(Token{TokenType::TOKEN_COLON});
    //     buffer.clear();
    // }
    // else if (m_source.at(i) == '(')
    // {
    //     tokens.push_back(Token{TokenType::TOKEN_LEFTPAR});
    // }
    // else if (m_source.at(i) == ')')
    // {
    //     tokens.push_back(Token{TokenType::TOKEN_RIGHTPAR});
    // }
    // else if (m_source.at(i) == ' ')
    // {
    //     continue;
    // }
    // }
    m_index = 0;
    return tokens;
}
const std::optional<char> Tokenizer::peak(int ahead) const
{
    if (m_index + ahead > m_source.length())
    {
        return {};
    }
    return m_source.at(m_index);
}

char Tokenizer::consume()
{
    return m_source.at(m_index++);
}
