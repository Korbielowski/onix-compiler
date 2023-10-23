#pragma once

#include "parser.hpp"

#include <string>

class Generator
{
public:
    Generator(NodeExit root);
    std::string generate() const;

private:
    const NodeExit m_root;
};