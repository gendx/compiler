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

#include "functionvisitor.hpp"

int FunctionVisitor::visit(AST& ast, std::ostream& err)
{
    FunctionVisitor v;
    ast.visit(v);
    return v.printErrors(err);
}


void FunctionVisitor::visit(Function& s)
{
    const std::string& name = s.mSignature->mIdentifier->token();
    std::shared_ptr<DecorationIdentifier> d = this->scope().lookupLocal(name);
    if (d && !d->isFunction())
        // TODO : use make_unique
        mErrors.push_back(std::unique_ptr<error::Error>(new error::AlreadyDeclared(*s.mSignature->mIdentifier, d->token())));
    else
        s.mSignature->mIdentifier->mDecoration = this->scope().set(name, s.shared_from_this());

    ScopeVisitor::visit(s);
}
