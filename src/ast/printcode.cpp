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

#include "printcode.hpp"
#include "../misc/colorizer.hpp"

#include <ostream>

void PrintCode::print(std::ostream& s, AST& ast, bool colorize)
{
    PrintCode v(s, colorize);
    ast.visit(v);
    s << std::endl;
}

PrintCode::PrintCode(std::ostream& s, bool colorize) :
    out(s), indent(-1), mColorize(colorize) {}


void PrintCode::endl()
{
    out << std::endl;
    for (int i = 0 ; i < indent ; ++i)
        out << "    ";
}

void PrintCode::keyword(const std::string& word)
{
    out << Colorizer(mColorize).bold().fg(Colorizer::blue) << word << Colorizer(mColorize).rst();
}


void PrintCode::visit(DecorationType&)
{
    out << Colorizer(mColorize).bold().fg(Colorizer::cyan);
}

void PrintCode::visit(DecorationFunction&)
{
    out << Colorizer(mColorize).bold().fg(Colorizer::red);
}

void PrintCode::visit(DecorationVariable&)
{
    out << Colorizer(mColorize).bold().fg(Colorizer::green);
}


void PrintCode::visit(LexicalError&)
{
    out << "<lexical error>";
}

void PrintCode::visit(ExprList& e)
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

void PrintCode::visit(Identifier& e)
{
    if (e.mDecoration)
        e.mDecoration->accept(*this);
    else
        out << Colorizer(mColorize).under();
    out << e.token();
    out << Colorizer(mColorize).rst();
}

void PrintCode::visit(Data& e)
{
    out << e.token();
}

void PrintCode::visit(DataString& e)
{
    out << e.token();
}

void PrintCode::visit(DataChar& e)
{
    out << e.token();
}

void PrintCode::visit(DataNumber& e)
{
    out << "(";
    out << e.token();
    out << ")";
}

void PrintCode::visit(Identify& e)
{
    e.mType->accept(*this);
    out << " ";
    e.mIdentifier->accept(*this);
}

void PrintCode::visit(Call& e)
{
    e.mExpression->accept(*this);
    out << "(";
    e.mArgs->accept(*this);
    out << ")";
}

void PrintCode::visit(Member& e)
{
    e.mExpression->accept(*this);
    out << ".";
    e.mMember->accept(*this);
}

void PrintCode::visit(Name& e)
{
    e.mName->accept(*this);
    if (e.mArgs)
    {
        out << "(";
        e.mArgs->accept(*this);
        out << ")";
    }
}

void PrintCode::visit(Signature& e)
{
    e.mType->accept(*this);
    out << " ";
    e.mIdentifier->accept(*this);
    out << "(";
    e.mArgs->accept(*this);
    out << ")";
}

void PrintCode::visit(Index& e)
{
    e.mExpression->accept(*this);
    out << "[";
    e.mArgs->accept(*this);
    out << "]";
}

void PrintCode::visit(Unary& e)
{
    out << "(" << Unary::opToStr(e.mOperator);
    e.mArg->accept(*this);
    out << ")";
}

void PrintCode::visit(Binary& e)
{
    out << "(";
    e.mLhs->accept(*this);
    out << Binary::opToStr(e.mOperator);
    e.mRhs->accept(*this);
    out << ")";
}


void PrintCode::visit(ExprStmt& s)
{
    this->endl();
    s.mExpression->accept(*this);
}

void PrintCode::visit(Return& s)
{
    this->endl();
    this->keyword("return");
    out << " ";
    s.mExpression->accept(*this);
}

void PrintCode::visit(Break&)
{
    this->endl();
    this->keyword("break");
}

void PrintCode::visit(Continue&)
{
    this->endl();
    this->keyword("continue");
}

void PrintCode::visit(Pass&)
{
    this->endl();
    this->keyword("pass");
}

void PrintCode::visit(Block& s)
{
    ++indent;
    for (auto&& it : s.mStatements)
        it->accept(*this);
    --indent;
}

void PrintCode::visit(Class& s)
{
    this->endl();
    this->keyword("class");
    out << " ";
    s.mName->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(Concept& s)
{
    this->endl();
    this->keyword("concept");
    out << " ";
    s.mName->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(Function& s)
{
    this->endl();
    this->keyword("def");
    out << " ";
    s.mSignature->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(Forever& s)
{
    this->endl();
    this->keyword("forever");
    s.mBlock->accept(*this);
}

void PrintCode::visit(While& s)
{
    this->endl();
    this->keyword("while");
    out << " ";
    s.mCondition->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(For& s)
{
    this->endl();
    this->keyword("for");
    out << " ";
    s.mVariable->accept(*this);
    out << " ";
    this->keyword("in");
    out << " ";
    s.mRange->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(If& s)
{
    bool begin = false;
    for (auto&& it : s.mConditions)
    {
        this->endl();
        if (begin)
        {
            this->keyword("elsif");
            out << " ";
        }
        else
        {
            this->keyword("if");
            out << " ";
        }
        begin = true;

        it.first->accept(*this);
        it.second->accept(*this);
    }

    if (s.mElse)
    {
        this->endl();
        this->keyword("else");
        s.mElse->accept(*this);
    }
}

void PrintCode::visit(Switch& s)
{
    this->endl();
    this->keyword("switch");
    out << " ";
    s.mExpression->accept(*this);

    for (auto&& it : s.mConditions)
    {
        this->endl();
        this->keyword("case");
        out << " ";
        it.first->accept(*this);
        it.second->accept(*this);
    }

    if (s.mDefault)
    {
        this->endl();
        this->keyword("default");
        s.mDefault->accept(*this);
    }
}

void PrintCode::visit(Match& s)
{
    this->endl();
    this->keyword("match");
    out << " ";
    s.mExpression->accept(*this);

    for (auto&& it : s.mConditions)
    {
        this->endl();
        this->keyword("with");
        out << " ";
        std::get<0>(it)->accept(*this);
        out << " ";
        this->keyword("as");
        out << " ";
        std::get<1>(it)->accept(*this);
        std::get<2>(it)->accept(*this);
    }
}
