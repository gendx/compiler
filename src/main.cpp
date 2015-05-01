/*
    Compiler - a test of flexc++/bisonc++ for a small programming language.
    Copyright (C) 2014 - 2015  G. Endignoux

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/gpl-3.0.txt
*/

#include "parse/Parser.h"
#include "ast/visit/printvisitor.hpp"
#include "ast/visit/printcode.hpp"
#include "ast/visit/symbolresolver.hpp"

int main()
{
    Parser parser;
    parser.parse();
    AST ast = parser.ast();

    if (ast.printErrors(std::cerr))
        return -1;

    int code = SymbolResolver::resolve(ast, std::cerr);
    if (code)
        return code;

    PrintVisitor::print(std::cerr, ast);
    PrintCode::print(std::cout, ast, true);
}
