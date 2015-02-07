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

#include "recursivevisitor.hpp"

void RecursiveVisitor::visit(LexicalError&)
{
}

void RecursiveVisitor::visit(ExprList& e)
{
    for (auto&& it : e.mExpressions)
        it->accept(*this);
}

void RecursiveVisitor::visit(Identifier&)
{
}

void RecursiveVisitor::visit(Data&)
{
}

void RecursiveVisitor::visit(DataString&)
{
}

void RecursiveVisitor::visit(DataChar&)
{
}

void RecursiveVisitor::visit(DataNumber&)
{
}

void RecursiveVisitor::visit(Identify& e)
{
    e.mType->accept(*this);
    e.mIdentifier->accept(*this);
}

void RecursiveVisitor::visit(Call& e)
{
    e.mExpression->accept(*this);
    e.mArgs->accept(*this);
}

void RecursiveVisitor::visit(Member& e)
{
    e.mExpression->accept(*this);
    e.mMember->accept(*this);
}

void RecursiveVisitor::visit(Name& e)
{
    e.mName->accept(*this);
    e.mArgs->accept(*this);
}

void RecursiveVisitor::visit(Signature& e)
{
    e.mType->accept(*this);
    e.mIdentifier->accept(*this);
    e.mArgs->accept(*this);
}

void RecursiveVisitor::visit(Index& e)
{
    e.mExpression->accept(*this);
    e.mArgs->accept(*this);
}

void RecursiveVisitor::visit(Unary& e)
{
    e.mArg->accept(*this);
}

void RecursiveVisitor::visit(Binary& e)
{
    e.mLhs->accept(*this);
    e.mRhs->accept(*this);
}


void RecursiveVisitor::visit(ExprStmt& s)
{
    s.mExpression->accept(*this);
}

void RecursiveVisitor::visit(Return& s)
{
    s.mExpression->accept(*this);
}

void RecursiveVisitor::visit(Break&)
{
}

void RecursiveVisitor::visit(Continue&)
{
}

void RecursiveVisitor::visit(Pass&)
{
}

void RecursiveVisitor::visit(Block& s)
{
    for (auto&& it : s.mStatements)
        it->accept(*this);
}

void RecursiveVisitor::visit(Class& s)
{
    s.mName->accept(*this);
    s.mBlock->accept(*this);
}

void RecursiveVisitor::visit(Concept& s)
{
    s.mName->accept(*this);
    s.mBlock->accept(*this);
}

void RecursiveVisitor::visit(Function& s)
{
    s.mSignature->accept(*this);
    s.mBlock->accept(*this);
}

void RecursiveVisitor::visit(Forever& s)
{
    s.mBlock->accept(*this);
}

void RecursiveVisitor::visit(While& s)
{
    s.mCondition->accept(*this);
    s.mBlock->accept(*this);
}

void RecursiveVisitor::visit(For& s)
{
    s.mVariable->accept(*this);
    s.mRange->accept(*this);
    s.mBlock->accept(*this);
}

void RecursiveVisitor::visit(If& s)
{
    for (auto&& it : s.mConditions)
    {
        it.first->accept(*this);
        it.second->accept(*this);
    }

    if (s.mElse)
        s.mElse->accept(*this);
}

void RecursiveVisitor::visit(Switch& s)
{
    s.mExpression->accept(*this);

    for (auto&& it : s.mConditions)
    {
        it.first->accept(*this);
        it.second->accept(*this);
    }

    if (s.mDefault)
        s.mDefault->accept(*this);
}

void RecursiveVisitor::visit(Match& s)
{
    s.mExpression->accept(*this);

    for (auto&& it : s.mConditions)
    {
        std::get<0>(it)->accept(*this);
        std::get<1>(it)->accept(*this);
        std::get<2>(it)->accept(*this);
    }
}


void RecursiveVisitor::visit(DecorationType&)
{
}

void RecursiveVisitor::visit(DecorationFunction&)
{
}

void RecursiveVisitor::visit(DecorationVariable&)
{
}
