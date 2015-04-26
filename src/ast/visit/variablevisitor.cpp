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

#include "variablevisitor.hpp"

bool VariableVisitor::visit(AST& ast, std::ostream& err)
{
    VariableVisitor v;
    ast.visit(v);
    for (auto&& e : v.mErrors)
        e->print(err);
    return v.mErrors.empty();
}


void VariableVisitor::visit(Identify& e)
{
    const std::string& name = e.mIdentifier->token();
    std::shared_ptr<DecorationIdentifier> d = this->scope().lookupLocal(name);
    if (d)
    {
        // TODO : use make_unique
        mErrors.push_back(std::unique_ptr<error::Error>(new error::AlreadyDeclared(*e.mIdentifier, d->token())));
        return;
    }

    std::shared_ptr<Type> type = e.mType->getType();
    if (!type)
    {
        // TODO : use make_unique
        mErrors.push_back(std::unique_ptr<error::Error>(new error::ExpectedType(*e.mType)));
        return;
    }

    e.mIdentifier->mDecoration = this->scope().set(name, e.shared_from_this());
    e.mIdentifier->mDecoration->mType = type;
}
