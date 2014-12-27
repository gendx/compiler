#include "parse/Parser.h"
#include "ast/printvisitor.hpp"

int main()
{
    Parser parser;
    parser.parse();
    AST ast = parser.ast();
    PrintVisitor::print(std::cout, ast);
}
