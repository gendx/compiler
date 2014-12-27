#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "expression.hpp"
#include "statement.hpp"

class Visitor
{
public:
    virtual ~Visitor();

    virtual void visit(ExprList& e) = 0;
    virtual void visit(Identifier& e) = 0;
    virtual void visit(Data& e) = 0;
    virtual void visit(DataString& e) = 0;
    virtual void visit(DataChar& e) = 0;
    virtual void visit(DataNumber& e) = 0;
    virtual void visit(Identify& e) = 0;
    virtual void visit(Call& e) = 0;
    virtual void visit(Member& e) = 0;
    virtual void visit(Method& e) = 0;
    virtual void visit(Signature& e) = 0;
    virtual void visit(Index& e) = 0;
    virtual void visit(Unary& e) = 0;
    virtual void visit(Binary& e) = 0;

    virtual void visit(ExprStmt& s) = 0;
    virtual void visit(Return& s) = 0;
    virtual void visit(Block& s) = 0;
    virtual void visit(Class& s) = 0;
    virtual void visit(Concept& s) = 0;
    virtual void visit(Function& s) = 0;
    virtual void visit(Forever& s) = 0;
    virtual void visit(While& s) = 0;
    virtual void visit(For& s) = 0;
    virtual void visit(If& s) = 0;
    virtual void visit(Switch& s) = 0;
    virtual void visit(Match& s) = 0;
};

#endif // VISITOR_HPP
