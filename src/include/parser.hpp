#pragma once

#include "tokenization.hpp"

struct NodeExpr
{
    Token int_lit;
};

struct NodeExit
{
    Token expr;
};

class Parser
{
public:
    Parser(std::vector<Token> tokens);
    std::optional<NodeExpr> parse_expr();
    std::optional<NodeExit> parse();

private:
    const std::vector<Token> m_tokens;
    size_t m_index = 0;

    const std::optional<Token> peek(int offset = 0) const;
    Token consume();
};