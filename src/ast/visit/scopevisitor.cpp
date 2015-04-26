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

void ScopeVisitor::visit(Block& s)
{
    std::shared_ptr<Scope> oldScope = mScope;

    mScope = this->getScope(s.mScope);
    RecursiveVisitor::visit(s);
    mScope = oldScope;
}

void ScopeVisitor::visit(Function& s)
{
    std::shared_ptr<Scope> oldScope = mScope;

    mSideScope = this->getScope(s.mScope);
    s.mSignature->accept(*this);
    mScope = mSideScope;
    s.mBlock->accept(*this);
    mScope = oldScope;
}

void ScopeVisitor::visit(Signature& e)
{
    e.mType->accept(*this);
    e.mIdentifier->accept(*this);

    //std::shared_ptr<Scope> oldScope = mScope;
    mScope = mSideScope;
    e.mParams->accept(*this);
    //mScope = oldScope;
}


std::shared_ptr<Scope>& ScopeVisitor::getScope(std::shared_ptr<Scope>& s)
{
    if (!s)
        s = std::make_shared<Scope>(mScope);
    return s;
}
