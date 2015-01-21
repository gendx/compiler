#include "printcode.hpp"

#include <ostream>

void PrintCode::print(std::ostream& s, AST& ast)
{
    PrintCode v(s);
    ast.visit(v);
    s << std::endl;
}

PrintCode::PrintCode(std::ostream& s) :
    out(s), indent(-1) {}


void PrintCode::endl()
{
    out << std::endl;
    for (unsigned int i = 0 ; i < indent ; ++i)
        out << "    ";
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
    out << e.mName;
}

void PrintCode::visit(Data& e)
{
    out << e.mValue;
}

void PrintCode::visit(DataString& e)
{
    out << e.mValue;
}

void PrintCode::visit(DataChar& e)
{
    out << e.mValue;
}

void PrintCode::visit(DataNumber& e)
{
    out << e.mValue;
}

void PrintCode::visit(Identify& e)
{
    e.mType->accept(*this);
    out << " ";
    e.mIdentifier->accept(*this);
}

void PrintCode::visit(Call& e)
{
    e.mIdentifier->accept(*this);
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

void PrintCode::visit(Method& e)
{
    e.mExpression->accept(*this);
    out << ".";
    e.mMethod->accept(*this);
}

void PrintCode::visit(Signature& e)
{
    e.mType->accept(*this);
    out << " ";
    e.mCall->accept(*this);
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
    out << "return ";
    s.mExpression->accept(*this);
}

void PrintCode::visit(Break& s)
{
    this->endl();
    out << "break";
}

void PrintCode::visit(Continue& s)
{
    this->endl();
    out << "continue";
}

void PrintCode::visit(Pass& s)
{
    this->endl();
    out << "pass";
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
    out << "class ";
    s.mName->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(Concept& s)
{
    this->endl();
    out << "concept ";
    s.mName->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(Function& s)
{
    this->endl();
    out << "def ";
    s.mSignature->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(Forever& s)
{
    this->endl();
    out << "forever";
    s.mBlock->accept(*this);
}

void PrintCode::visit(While& s)
{
    this->endl();
    out << "while ";
    s.mCondition->accept(*this);
    s.mBlock->accept(*this);
}

void PrintCode::visit(For& s)
{
    this->endl();
    out << "for ";
    s.mVariable->accept(*this);
    out << " in ";
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
            out << "elsif ";
        else
            out << "if ";
        begin = true;

        it.first->accept(*this);
        it.second->accept(*this);
    }

    if (s.mElse)
    {
        this->endl();
        out << "else";
        s.mElse->accept(*this);
    }
}

void PrintCode::visit(Switch& s)
{
    this->endl();
    out << "switch ";
    s.mExpression->accept(*this);

    for (auto&& it : s.mConditions)
    {
        this->endl();
        out << "case ";
        it.first->accept(*this);
        it.second->accept(*this);
    }

    if (s.mDefault)
    {
        this->endl();
        out << "default";
        s.mDefault->accept(*this);
    }
}

void PrintCode::visit(Match& s)
{
    this->endl();
    out << "match ";
    s.mExpression->accept(*this);

    for (auto&& it : s.mConditions)
    {
        this->endl();
        out << "with ";
        std::get<0>(it)->accept(*this);
        out << " as ";
        std::get<1>(it)->accept(*this);
        std::get<2>(it)->accept(*this);
    }
}
