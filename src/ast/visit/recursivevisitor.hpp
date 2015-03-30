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

#ifndef RECURSIVEVISITOR_HPP
#define RECURSIVEVISITOR_HPP

#include "emptyvisitor.hpp"

class RecursiveVisitor : public EmptyVisitor
{
public:
    void visit(ExprList& e);
    void visit(Identify& e);
    void visit(Parameters& e);
    void visit(Call& e);
    void visit(Member& e);
    void visit(Name& e);
    void visit(Signature& e);
    void visit(Index& e);
    void visit(Unary& e);
    void visit(Binary& e);

    void visit(ExprStmt& s);
    void visit(Return& s);
    void visit(Block& s);
    void visit(Class& s);
    void visit(Concept& s);
    void visit(Function& s);
    void visit(Forever& s);
    void visit(While& s);
    void visit(For& s);
    void visit(If& s);
    void visit(Switch& s);
    void visit(Match& s);
};

#endif // RECURSIVEVISITOR_HPP
