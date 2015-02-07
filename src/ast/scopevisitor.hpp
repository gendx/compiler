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

#ifndef SCOPEVISITOR_HPP
#define SCOPEVISITOR_HPP

#include "recursivevisitor.hpp"
#include "ast.hpp"
#include <stack>

class ScopeVisitor : public RecursiveVisitor
{
public:
    static void visit(AST& ast);

    void visit(Identifier& e);
    void visit(Identify& e);

    void visit(Block& s);
    void visit(Class& s);
    void visit(Function& s);

private:
    ScopeVisitor();

    std::stack<std::shared_ptr<Scope> > mScopes;
};

#endif // SCOPEVISITOR_HPP
