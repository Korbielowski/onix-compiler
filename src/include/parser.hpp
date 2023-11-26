#pragma once

#include <variant>

#include "tokenizer.hpp"

struct NodeExprIntLit {
  Token int_lit;
};

struct NodeExprIdent {
  Token ident;
};

struct NodeExpr {
  std::variant<NodeExprIdent, NodeExprIntLit> variants_expr;
};

struct NodeStatExit {
  NodeExpr expr_exit;
};

struct NodeStatVar {
  Token ident;
  NodeExpr expr_var;
};

struct NodeStat {
  std::variant<NodeStatExit, NodeStatVar> variants_stat;
};

struct NodeProg {
  std::vector<NodeStat> statements;
};

class Parser {
 public:
  Parser(std::vector<Token> tokens);
  std::optional<NodeExpr> parse_expr();
  std::optional<NodeStat> parse_stat();
  std::optional<NodeProg> parse_prog();

 private:
  const std::vector<Token> m_tokens;
  size_t m_index = 0;

  const std::optional<Token> peek(int offset = 0) const;
  Token consume_token();
};