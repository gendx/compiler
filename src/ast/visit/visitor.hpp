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

#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "../expression.hpp"
#include "../statement.hpp"

class Visitor
{
public:
    virtual ~Visitor();

    virtual void visit(LexicalError& e) = 0;
    virtual void visit(ExprList& e) = 0;
    virtual void visit(Identifier& e) = 0;
    virtual void visit(Data& e) = 0;
    virtual void visit(DataString& e) = 0;
    virtual void visit(DataChar& e) = 0;
    virtual void visit(DataNumber& e) = 0;
    virtual void visit(Identify& e) = 0;
    virtual void visit(Parameters& e) = 0;
    virtual void visit(Call& e) = 0;
    virtual void visit(Member& e) = 0;
    virtual void visit(Name& e) = 0;
    virtual void visit(Signature& e) = 0;
    virtual void visit(Index& e) = 0;
    virtual void visit(Unary& e) = 0;
    virtual void visit(Binary& e) = 0;

    virtual void visit(ExprStmt& s) = 0;
    virtual void visit(Return& s) = 0;
    virtual void visit(Break& s) = 0;
    virtual void visit(Continue& s) = 0;
    virtual void visit(Pass& s) = 0;
    virtual void visit(Block& s) = 0;
    virtual void visit(Class& s) = 0;
    virtual void visit(Concept& s) = 0;
    virtual void visit(Function& s) = 0;
    virtual void visit(Forever& s) = 0;
    virtual void visit(While& s) = 0;
    virtual void visit(For& s) = 0;
    virtual void visit(If& s) = 0;
    virtual void visit(Switch& s) = 0;
    virtual void visit(Match& s) = 0;

    virtual void visit(DecorationValue& d) = 0;
    virtual void visit(DecorationType& d) = 0;
    virtual void visit(DecorationFunction& d) = 0;
    virtual void visit(DecorationVariable& d) = 0;
};

#endif // VISITOR_HPP
