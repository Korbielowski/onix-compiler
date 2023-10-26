#include "include/generation.hpp"

Generator::Generator(NodeExit root) : m_root(std::move(root))
{
}

std::string Generator::generate() const
{
    std::stringstream output;
    output << "global _start\nstart:\n";
    output << "     mov rax, 60\n";
    output << "     mov rdi, " << m_root.expr.value.value() << "\n";
    output << "     syscall";

    return output.str();
}