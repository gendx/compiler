#ifndef AST_HPP
#define AST_HPP

#include "statement.hpp"

class AST
{
public:
    AST();
    AST(std::shared_ptr<Block> root);

    void visit(Visitor& v);

private:
    std::shared_ptr<Block> mRoot;
};

#endif // AST_HPP
