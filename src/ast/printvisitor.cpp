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

#include "printvisitor.hpp"

#include <ostream>

void PrintVisitor::print(std::ostream& s, AST& ast)
{
    PrintVisitor v(s);
    ast.visit(v);
    s << std::endl;
}

PrintVisitor::PrintVisitor(std::ostream& s) :
    out(s) {}


void PrintVisitor::visit(DecorationType&)
{
    out << "<type>";
}

void PrintVisitor::visit(DecorationFunction&)
{
    out << "<function>";
}

void PrintVisitor::visit(DecorationVariable&)
{
    out << "<variable>";
}


void PrintVisitor::visit(LexicalError&)
{
    out << "<lexical error>";
}

void PrintVisitor::visit(ExprList& e)
{
    bool begin = false;
    for (auto&& it : e.mExpressions)
    {
        if (begin)
            out << ", ";
        begin = true;
        it->accept(*this);
    }
}

void PrintVisitor::visit(Identifier& e)
{
    out << "(" << e.token() << " $ ";
    if (e.mDecoration)
        e.mDecoration->accept(*this);
    else
        out << "<undeclared>";
    out << ")";
}

void PrintVisitor::visit(Data& e)
{
    out << e.token();
}

void PrintVisitor::visit(DataString& e)
{
    out << e.token();
}

void PrintVisitor::visit(DataChar& e)
{
    out << e.token();
}

void PrintVisitor::visit(DataNumber& e)
{
    out << "(";
    out << e.token();
    out << ")";
}

void PrintVisitor::visit(Identify& e)
{
    out << "(";
    e.mType->accept(*this);
    out << "#";
    e.mIdentifier->accept(*this);
    out << ")";
}

void PrintVisitor::visit(Call& e)
{
    out << "(";
    e.mExpression->accept(*this);
    out << "(";
    e.mArgs->accept(*this);
    out << "))";
}

void PrintVisitor::visit(Member& e)
{
    out << "(";
    e.mExpression->accept(*this);
    out << ".";
    e.mMember->accept(*this);
    out << ")";
}

void PrintVisitor::visit(Name& e)
{
    out << "(";
    e.mName->accept(*this);
    if (e.mArgs)
    {
        out << "(";
        e.mArgs->accept(*this);
        out << ")";
    }
    out << ")";
}

void PrintVisitor::visit(Signature& e)
{
    out << "(";
    e.mType->accept(*this);
    out << "#";
    e.mIdentifier->accept(*this);
    out << "(";
    e.mArgs->accept(*this);
    out << ")";
    out << ")";
}

void PrintVisitor::visit(Index& e)
{
    out << "(";
    e.mExpression->accept(*this);
    out << "[";
    e.mArgs->accept(*this);
    out << "])";
}

void PrintVisitor::visit(Unary& e)
{
    out << "(" << Unary::opToStr(e.mOperator);
    e.mArg->accept(*this);
    out << ")";
}

void PrintVisitor::visit(Binary& e)
{
    out << "(";
    e.mLhs->accept(*this);
    out << Binary::opToStr(e.mOperator);
    e.mRhs->accept(*this);
    out << ")";
}


void PrintVisitor::visit(Return& s)
{
    out << "return(";
    s.mExpression->accept(*this);
    out << ")";
}

void PrintVisitor::visit(Break&)
{
    out << "break";
}

void PrintVisitor::visit(Continue&)
{
    out << "continue";
}

void PrintVisitor::visit(Pass&)
{
    out << "pass";
}

void PrintVisitor::visit(Block& s)
{
    bool begin = false;
    for (auto&& it : s.mStatements)
    {
        if (begin)
            out << "; ";
        begin = true;
        it->accept(*this);
    }
}

void PrintVisitor::visit(Class& s)
{
    out << "class(";
    s.mName->accept(*this);
    out << " : ";
    s.mBlock->accept(*this);
    out << ")";
}

void PrintVisitor::visit(Concept& s)
{
    out << "concept(";
    s.mName->accept(*this);
    out << " : ";
    s.mBlock->accept(*this);
    out << ")";
}

void PrintVisitor::visit(Function& s)
{
    out << "def(";
    s.mSignature->accept(*this);
    out << " : ";
    s.mBlock->accept(*this);
    out << ")";
}

void PrintVisitor::visit(Forever& s)
{
    out << "forever(";
    s.mBlock->accept(*this);
    out << ")";
}

void PrintVisitor::visit(While& s)
{
    out << "while(";
    s.mCondition->accept(*this);
    out << " : ";
    s.mBlock->accept(*this);
    out << ")";
}

void PrintVisitor::visit(For& s)
{
    out << "for(";
    s.mVariable->accept(*this);
    out << " in ";
    s.mRange->accept(*this);
    out << " : ";
    s.mBlock->accept(*this);
    out << ")";
}

void PrintVisitor::visit(If& s)
{
    out << "if(";

    bool begin = false;
    for (auto&& it : s.mConditions)
    {
        if (begin)
            out << ", ";
        begin = true;

        it.first->accept(*this);
        out << " : ";
        it.second->accept(*this);
    }

    if (s.mElse)
    {
        out << ", ";
        s.mElse->accept(*this);
    }
    out << ")";
}

void PrintVisitor::visit(Switch& s)
{
    out << "switch(";
    s.mExpression->accept(*this);
    out << ", ";

    bool begin = false;
    for (auto&& it : s.mConditions)
    {
        if (begin)
            out << ", ";
        begin = true;

        it.first->accept(*this);
        out << " : ";
        it.second->accept(*this);
    }

    if (s.mDefault)
    {
        out << ", default : ";
        s.mDefault->accept(*this);
    }
    out << ")";
}

void PrintVisitor::visit(Match& s)
{
    out << "match(";
    s.mExpression->accept(*this);
    out << ", ";

    bool begin = false;
    for (auto&& it : s.mConditions)
    {
        if (begin)
            out << ", ";
        begin = true;

        std::get<0>(it)->accept(*this);
        out << " @ ";
        std::get<1>(it)->accept(*this);
        out << " : ";
        std::get<2>(it)->accept(*this);
    }

    out << ")";
}
