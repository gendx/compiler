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

#ifndef VARIABLEVISITOR_HPP
#define VARIABLEVISITOR_HPP

#include "recursivevisitor.hpp"
#include "../ast.hpp"
#include "../error/error.hpp"

class VariableVisitor : public RecursiveVisitor
{
public:
    static bool visit(AST& ast, std::ostream& err);

    void visit(Block& s);
    void visit(Identify& e);

private:
    VariableVisitor() = default;

    std::shared_ptr<Scope> mScope;
    std::vector<std::unique_ptr<error::Error> > mErrors;
};

#endif // VARIABLEVISITOR_HPP
