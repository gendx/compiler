#include "parse/Parser.h"
#include "ast/printvisitor.hpp"
#include "ast/printcode.hpp"

int main()
{
    Parser parser;
    parser.parse();
    AST ast = parser.ast();
    PrintVisitor::print(std::cout, ast);
    PrintCode::print(std::cerr, ast);
}
