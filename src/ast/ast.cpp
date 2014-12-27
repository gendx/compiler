#include "ast.hpp"

AST::AST()
{
}

AST::AST(std::shared_ptr<Block> root) :
    mRoot(root)
{
}


void AST::visit(Visitor& v)
{
    mRoot->accept(v);
}
