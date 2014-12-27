#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "expression.hpp"
#include <algorithm>

class Visitor;

/** Statement **/
class Statement
{
public:
    virtual ~Statement();

    virtual void accept(Visitor& v) = 0;
};


/** ExprStmt **/
class ExprStmt : public Statement
{
public:
    inline ExprStmt(std::shared_ptr<Expression> e) :
        mExpression(e) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
};


/** Return **/
class Return : public Statement
{
public:
    inline Return(std::shared_ptr<Expression> e) :
        mExpression(e) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
};


/** Block **/
class Block : public Statement
{
public:
    inline Block()
        {}

    inline void append(std::shared_ptr<Statement> s)
        {mStatements.push_back(s);}
    inline void reverse()
        {std::reverse(mStatements.begin(), mStatements.end());}

    void accept(Visitor& v);

    std::vector<std::shared_ptr<Statement> > mStatements;
};


/** Class **/
class Class : public Statement
{
public:
    inline Class(std::shared_ptr<Identifier> name, std::shared_ptr<Block> block) :
        mName(name), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Identifier> mName;
    std::shared_ptr<Block> mBlock;
};


/** Concept **/
class Concept : public Statement
{
public:
    inline Concept(std::shared_ptr<Identifier> name, std::shared_ptr<Block> block) :
        mName(name), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Identifier> mName;
    std::shared_ptr<Block> mBlock;
};


/** Function **/
class Function : public Statement
{
public:
    inline Function(std::shared_ptr<Expression> signature, std::shared_ptr<Block> block) :
        mSignature(signature), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mSignature;
    std::shared_ptr<Block> mBlock;
};


/** Forever **/
class Forever : public Statement
{
public:
    inline Forever(std::shared_ptr<Block> block) :
        mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Block> mBlock;
};


/** While **/
class While : public Statement
{
public:
    inline While(std::shared_ptr<Expression> condition, std::shared_ptr<Block> block) :
        mCondition(condition), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mCondition;
    std::shared_ptr<Block> mBlock;
};


/** For **/
class For : public Statement
{
public:
    inline For(std::shared_ptr<Expression> variable, std::shared_ptr<Expression> range, std::shared_ptr<Block> block) :
        mVariable(variable), mRange(range), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mVariable;
    std::shared_ptr<Expression> mRange;
    std::shared_ptr<Block> mBlock;
};


/** If **/
class If : public Statement
{
public:
    inline If()
        {}
    inline If(std::shared_ptr<Block> _else) :
        mElse(_else) {}

    inline void append(std::shared_ptr<Expression> condition, std::shared_ptr<Block> block)
        {mConditions.push_back(std::make_pair(condition, block));}
    inline void reverse()
        {std::reverse(mConditions.begin(), mConditions.end());}

    void accept(Visitor& v);

    std::vector<std::pair<std::shared_ptr<Expression>, std::shared_ptr<Block> > > mConditions;
    std::shared_ptr<Block> mElse;
};


/** Switch **/
class Switch : public Statement
{
public:
    inline Switch()
        {}
    inline Switch(std::shared_ptr<Block> _default) :
        mDefault(_default) {}


    inline void setExpr(std::shared_ptr<Expression> expression)
        {mExpression = expression;}
    inline void append(std::shared_ptr<Expression> condition, std::shared_ptr<Block> block)
        {mConditions.push_back(std::make_pair(condition, block));}
    inline void reverse()
        {std::reverse(mConditions.begin(), mConditions.end());}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
    std::vector<std::pair<std::shared_ptr<Expression>, std::shared_ptr<Block> > > mConditions;
    std::shared_ptr<Block> mDefault;
};


/** Match **/
class Match : public Statement
{
public:
    inline Match()
        {}

    inline void setExpr(std::shared_ptr<Expression> expression)
        {mExpression = expression;}
    inline void append(std::shared_ptr<Expression> condition, std::shared_ptr<Identifier> identifier, std::shared_ptr<Block> block)
        {mConditions.push_back(std::make_tuple(condition, identifier, block));}
    inline void reverse()
        {std::reverse(mConditions.begin(), mConditions.end());}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
    std::vector<std::tuple<std::shared_ptr<Expression>, std::shared_ptr<Identifier>, std::shared_ptr<Block> > > mConditions;
};

#endif // STATEMENT_HPP
