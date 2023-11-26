#include "include/parser.hpp"
#include "include/ansi_colors.hpp"
#include "include/print_tokens.hpp"

Parser::Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {}

std::optional<NodeExpr>
Parser::parse_expr() {
    if (peek().has_value() && peek().value().type == TokenType::TOKEN_INT) {
        return NodeExpr{.variants_expr = NodeExprIntLit{.int_lit = consume_token()}};
    } else if (peek().has_value() && peek().value().type == TokenType::TOKEN_VAR_IDENT) {
        return NodeExpr{.variants_expr = NodeExprIdent{.ident = consume_token()}};
    }
}

std::optional<NodeStat>
Parser::parse_stat() {
    if (peek().has_value() && peek().value().type == TokenType::TOKEN_RETURN) {
        consume_token();
        NodeStatExit statement_exit;
        if (auto node_expr = parse_expr()) {
            statement_exit = {.expr_exit = node_expr.value()};
        } else {
            std::cerr << RED_TEXT << "ERROR\n" << DEFAULT_TEXT << "Missing expression\n";
            exit(EXIT_FAILURE);
        }
        if (peek().has_value() && peek().value().type == TokenType::TOKEN_SEMI) {
            consume_token();
        } else {
            std::cerr << RED_TEXT << "Error\n" << DEFAULT_TEXT << "Expected ';'\n";
            exit(EXIT_FAILURE);
        }
        return NodeStat{.variants_stat = statement_exit};
    } else if (peek().has_value() && peek().value().type == TokenType::TOKEN_IDENT_INT &&
               peek(1).has_value() && peek(1).value().type == TokenType::TOKEN_VAR_IDENT &&
               peek(2).has_value() && peek(2).value().type == TokenType::TOKEN_EQUAL) {
        consume_token();
        auto stat_var = NodeStatVar{.ident = consume_token()};
        consume_token();
        if (auto node_expr = parse_expr()) {
            stat_var.expr_var = node_expr.value();
        } else {
            std::cerr << RED_TEXT << "ERROR\n" << DEFAULT_TEXT << "Invalid expression\n";
            exit(EXIT_FAILURE);
        }
        if (peek().has_value() && peek().value().type == TokenType::TOKEN_SEMI) {
            consume_token();
        } else {
            std::cerr << RED_TEXT << "Error\n" << DEFAULT_TEXT << "Expected ';'\n";
            exit(EXIT_FAILURE);
        }
        return NodeStat{.variants_stat = stat_var};
    } else {
        return {};
    }
}

std::optional<NodeProg>
Parser::parse_prog() {
    NodeProg prog;
    while (peek().has_value()) {
        if (auto stat = parse_stat()) {
            prog.statements.push_back(stat.value());
        } else {
            std::cerr << RED_TEXT << "ERROR\n" << DEFAULT_TEXT << "Invalid statement\n";
            exit(EXIT_FAILURE);
        }
    }
    return prog;
}

const std::optional<Token>
Parser::peek(int offset) const {
    if (m_index + offset >= m_tokens.size()) {
        return {};
    }
    return m_tokens.at(m_index + offset);
}

Token
Parser::consume_token() {
    print_token(m_tokens.at(m_index));
    return m_tokens.at(m_index++);
}