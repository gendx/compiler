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

#include "statement.hpp"
#include "visit/visitor.hpp"

Statement::~Statement()
{
}


void ExprStmt::accept(Visitor& v)
{
    v.visit(*this);
}
void Return::accept(Visitor& v)
{
    v.visit(*this);
}
void Break::accept(Visitor& v)
{
    v.visit(*this);
}
void Continue::accept(Visitor& v)
{
    v.visit(*this);
}
void Pass::accept(Visitor& v)
{
    v.visit(*this);
}
void Block::accept(Visitor& v)
{
    v.visit(*this);
}
void Class::accept(Visitor& v)
{
    v.visit(*this);
}
void Concept::accept(Visitor& v)
{
    v.visit(*this);
}
void Function::accept(Visitor& v)
{
    v.visit(*this);
}
void Forever::accept(Visitor& v)
{
    v.visit(*this);
}
void While::accept(Visitor& v)
{
    v.visit(*this);
}
void For::accept(Visitor& v)
{
    v.visit(*this);
}
void If::accept(Visitor& v)
{
    v.visit(*this);
}
void Switch::accept(Visitor& v)
{
    v.visit(*this);
}
void Match::accept(Visitor& v)
{
    v.visit(*this);
}
