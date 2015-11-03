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

#include "typevisitor.hpp"

int TypeVisitor::visit(AST& ast, std::ostream& err)
{
    TypeVisitor v;
    ast.visit(v);
    return v.printErrors(err);
}


void TypeVisitor::visit(Identifier& e)
{
    e.mDecoration = this->scope().lookup(e.token());
}

void TypeVisitor::visit(Index& e)
{
    RecursiveVisitor::visit(e);

    std::shared_ptr<Type> type = e.mExpression->getType();
    if (type)
    {
        if (!type->parameters().empty())
        {
            mErrors.push_back(std::make_unique<error::AlreadyQualifiedType>(*e.mExpression, *e.mArgs));
            return;
        }

        std::vector<Type> args;

        for (auto&& arg : e.mArgs->mExpressions)
        {
            std::shared_ptr<Type> argType = arg->getType();
            if (!argType)
                mErrors.push_back(std::make_unique<error::ExpectedType>(*arg));
            else
                args.push_back(*argType);
        }

        if (args.empty())
            mErrors.push_back(std::make_unique<error::EmptyTypeQualification>(e));

        e.mDecoration = std::make_shared<DecorationType>(type->definition(), args);
    }
}
