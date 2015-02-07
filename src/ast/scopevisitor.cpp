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

#include "scopevisitor.hpp"

void ScopeVisitor::visit(AST& ast)
{
    ScopeVisitor v;
    ast.visit(v);
}

ScopeVisitor::ScopeVisitor()
{
    mScopes.push(std::make_shared<Scope>());
}


void ScopeVisitor::visit(Identifier& e)
{
    e.mDecoration = mScopes.top()->lookup(e.token());
}

void ScopeVisitor::visit(Identify& e)
{
    e.mType->accept(*this);
    mScopes.top()->set(e.mIdentifier->token(), e.shared_from_this());
}


void ScopeVisitor::visit(Block& s)
{
    std::shared_ptr<Scope> scope = std::make_shared<Scope>(mScopes.top());
    s.mScope = scope;

    mScopes.push(scope);
    RecursiveVisitor::visit(s);
    mScopes.pop();
}

void ScopeVisitor::visit(Class& s)
{
    mScopes.top()->set(s.mName->token(), s.shared_from_this());
    s.mBlock->accept(*this);
}

void ScopeVisitor::visit(Function& s)
{
    s.mSignature->accept(*this);
    mScopes.top()->set(s.mSignature->mIdentifier->token(), s.shared_from_this());
    s.mBlock->accept(*this);
}
