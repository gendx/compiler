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

#include "decoration.hpp"

#include "visit/visitor.hpp"

Decoration::~Decoration()
{
}

const Token& DecorationType::token() const
{
    return *(mType->definition().lock()->mName->mName);
}
const Token& DecorationFunction::token() const
{
    return *(mFunction.lock()->mSignature->mIdentifier);
}
const Token& DecorationVariable::token() const
{
    return *(mIdentify.lock()->mIdentifier);
}

void DecorationValue::accept(Visitor& v)
{
    v.visit(*this);
}
void DecorationType::accept(Visitor& v)
{
    v.visit(*this);
}
void DecorationFunction::accept(Visitor& v)
{
    v.visit(*this);
}
void DecorationVariable::accept(Visitor& v)
{
    v.visit(*this);
}


bool Decoration::isValue()
{
    return false;
}
bool Decoration::isIdentifier()
{
    return false;
}
bool Decoration::isType()
{
    return false;
}
bool Decoration::isFunction()
{
    return false;
}
bool Decoration::isVariable()
{
    return false;
}

bool DecorationValue::isValue()
{
    return true;
}
bool DecorationIdentifier::isIdentifier()
{
    return true;
}
bool DecorationType::isType()
{
    return true;
}
bool DecorationFunction::isFunction()
{
    return true;
}
bool DecorationVariable::isVariable()
{
    return true;
}
