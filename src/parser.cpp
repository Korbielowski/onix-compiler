#include "include/parser.hpp"

Parser::Parser(std::vector<Token> tokens)
    : m_tokens(std::move(tokens))
{
}

std::optional<NodeExpr> Parser::parse_expr()
{
    if (peek().has_value() && peek().value().type == TokenType::TOKEN_INT)
    {
        NodeExpr node_expr = NodeExpr{};
        node_expr.int_lit = consume();
        return node_expr;
    }
    return {};
}

std::optional<NodeExit> Parser::parse()
{
    std::optional<NodeExit> exit_node;
    while (peek().has_value())
    {
        switch (peek().value().type)
        {
        case TokenType::TOKEN_RETURN:
        {
            consume();
            auto node_expr = parse_expr();
            if (!node_expr.has_value())
            {
                std::cerr << "Invalid expression missing expression\n";
                exit(EXIT_FAILURE);
            }
            else
            {
                NodeExit node_value = NodeExit{};
                node_value.expr = node_expr.value().int_lit;
                exit_node = node_value;
            }
            if (peek().has_value() || peek().value().type == TokenType::TOKEN_SEMI)
            {
                consume();
            }
            else
            {
                std::cerr << "Expected ';'\n";
                exit(EXIT_FAILURE);
            }
            break;
        }
        case TokenType::TOKEN_IF:
        {
        }
        case TokenType::TOKEN_WHILE:
        {
        }
        }

        // if (peek().value().type == TokenType::TOKEN_RETURN)
        // {
        // }
    }
    m_index = 0;
    return exit_node;
}

const std::optional<Token> Parser::peek(int offset) const
{
    if (m_index + offset >= m_tokens.size())
    {
        return {};
    }
    return m_tokens.at(m_index + offset);
}

Token Parser::consume()
{
    return m_tokens.at(m_index++);
}