#ifndef PRINTCODE_HPP
#define PRINTCODE_HPP

#include "visitor.hpp"
#include "ast.hpp"

class PrintCode : public Visitor
{
public:
    static void print(std::ostream& s, AST& ast);

    void visit(ExprList& e);
    void visit(Identifier& e);
    void visit(Data& e);
    void visit(DataString& e);
    void visit(DataChar& e);
    void visit(DataNumber& e);
    void visit(Identify& e);
    void visit(Call& e);
    void visit(Member& e);
    void visit(Method& e);
    void visit(Signature& e);
    void visit(Index& e);
    void visit(Unary& e);
    void visit(Binary& e);

    void visit(ExprStmt& s);
    void visit(Return& s);
    void visit(Break& s);
    void visit(Continue& s);
    void visit(Pass& s);
    void visit(Block& s);
    void visit(Class& s);
    void visit(Concept& s);
    void visit(Function& s);
    void visit(Forever& s);
    void visit(While& s);
    void visit(For& s);
    void visit(If& s);
    void visit(Switch& s);
    void visit(Match& s);

private:
    PrintCode(std::ostream& s);

    void endl();

    std::ostream& out;
    int indent;
};

#endif // PRINTCODE_HPP
