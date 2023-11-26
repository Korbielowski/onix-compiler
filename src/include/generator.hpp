#pragma once

#include <string>
#include <unordered_map>

#include "parser.hpp"

struct Var {
  size_t stack_loc;
};

class Generator {
 public:
  Generator(NodeProg prog);
  std::string generate_prog();
  void generate_stat(const NodeStat &stat);
  void generate_expr(const NodeExpr &expr);

 private:
  const NodeProg m_prog;
  std::stringstream m_output;
  size_t m_stack_size = 0;
  std::unordered_map<std::string, Var> m_vars{};

  void push_var(const std::string &reg);
  void pop_var(const std::string &reg);
};