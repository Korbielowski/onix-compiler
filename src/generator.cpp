#include "include/generator.hpp"

Generator::Generator(NodeProg prog) : m_prog(std::move(prog)) {}

void
Generator::generate_expr(const NodeExpr &expr) {
    struct ExprVisitor {
        Generator *gen;
        void operator()(const NodeExprIntLit &expr_int_lit) {
            gen->m_output << "    mov rax, " << expr_int_lit.int_lit.value.value() << "\n";
            gen->push_var("rax");
        }
        void operator()(const NodeExprIdent &expr_ident) {
            if (!gen->m_vars.contains(expr_ident.ident.value.value())) {
                std::cerr << "Undeclared identifier: " << expr_ident.ident.value.value()
                          << std::endl;
                exit(EXIT_FAILURE);
            }
            const auto &var = gen->m_vars.at(expr_ident.ident.value.value());
            std::stringstream offset;
            offset << "QWORD [rsp - " << (gen->m_stack_size - var.stack_loc - 1) * 8 << "]\n";
            gen->push_var(offset.str());
        }
    };
    ExprVisitor visitor{.gen = this};
    std::visit(visitor, expr.variants_expr);
}

void
Generator::generate_stat(const NodeStat &stat) {
    struct StatVisitor {
        Generator *gen;
        void operator()(const NodeStatExit &stat_exit) {
            gen->generate_expr(stat_exit.expr_exit);
            // TODO: Add assembly for custom return/exit
            gen->m_output << "    mov rax, 60\n";
            gen->pop_var("rdi");
            gen->m_output << "    syscall\n";
        }
        void operator()(const NodeStatVar &stat_var) {
            if (gen->m_vars.contains(stat_var.ident.value.value())) {
                std::cerr << "Identifier already used: " << stat_var.ident.value.value()
                          << std::endl;
                exit(EXIT_FAILURE);
            }
            gen->m_vars.insert({stat_var.ident.value.value(), Var{.stack_loc = gen->m_stack_size}});
            gen->generate_expr(stat_var.expr_var);
        }
    };
    StatVisitor visitor{.gen = this};
    std::visit(visitor, stat.variants_stat);
}

std::string
Generator::generate_prog() {
    std::stringstream m_output;
    this->m_output << "global _start\n_start:\n";

    for (const NodeStat &stat : m_prog.statements) {
        generate_stat(stat);
    }
    this->m_output << "    mov rax, 60\n";
    this->m_output << "    mov rdi, 0\n";
    this->m_output << "    syscall";

    return this->m_output.str();
}

void
Generator::push_var(const std::string &reg) {
    m_output << "    push " << reg << "\n";
    m_stack_size++;
}

void
Generator::pop_var(const std::string &reg) {
    m_output << "    pop " << reg << "\n";
    m_stack_size--;
}