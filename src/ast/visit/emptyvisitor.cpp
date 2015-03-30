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

#include "emptyvisitor.hpp"

void EmptyVisitor::visit(LexicalError&)
{
}
void EmptyVisitor::visit(ExprList&)
{
}
void EmptyVisitor::visit(Identifier&)
{
}
void EmptyVisitor::visit(Data&)
{
}
void EmptyVisitor::visit(DataString&)
{
}
void EmptyVisitor::visit(DataChar&)
{
}
void EmptyVisitor::visit(DataNumber&)
{
}
void EmptyVisitor::visit(Identify&)
{
}
void EmptyVisitor::visit(Parameters&)
{
}
void EmptyVisitor::visit(Call&)
{
}
void EmptyVisitor::visit(Member&)
{
}
void EmptyVisitor::visit(Name&)
{
}
void EmptyVisitor::visit(Signature&)
{
}
void EmptyVisitor::visit(Index&)
{
}
void EmptyVisitor::visit(Unary&)
{
}
void EmptyVisitor::visit(Binary&)
{
}

void EmptyVisitor::visit(ExprStmt&)
{
}
void EmptyVisitor::visit(Return&)
{
}
void EmptyVisitor::visit(Break&)
{
}
void EmptyVisitor::visit(Continue&)
{
}
void EmptyVisitor::visit(Pass&)
{
}
void EmptyVisitor::visit(Block&)
{
}
void EmptyVisitor::visit(Class&)
{
}
void EmptyVisitor::visit(Concept&)
{
}
void EmptyVisitor::visit(Function&)
{
}
void EmptyVisitor::visit(Forever&)
{
}
void EmptyVisitor::visit(While&)
{
}
void EmptyVisitor::visit(For&)
{
}
void EmptyVisitor::visit(If&)
{
}
void EmptyVisitor::visit(Switch&)
{
}
void EmptyVisitor::visit(Match&)
{
}

void EmptyVisitor::visit(DecorationValue&)
{
}
void EmptyVisitor::visit(DecorationType&)
{
}
void EmptyVisitor::visit(DecorationFunction&)
{
}
void EmptyVisitor::visit(DecorationVariable&)
{
}
