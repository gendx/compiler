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

#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <algorithm>
#include "expression.hpp"
#include "scope.hpp"

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


/** Break **/
class Break : public Statement
{
public:
    Break() = default;

    void accept(Visitor& v);
};


/** Continue **/
class Continue : public Statement
{
public:
    Continue() = default;

    void accept(Visitor& v);
};


/** Pass **/
class Pass : public Statement
{
public:
    Pass() = default;

    void accept(Visitor& v);
};


/** Block **/
class Block : public Statement
{
public:
    Block() = default;

    inline void append(std::shared_ptr<Statement> s)
        {mStatements.push_back(s);}
    inline void reverse()
        {std::reverse(mStatements.begin(), mStatements.end());}

    void accept(Visitor& v);

    std::vector<std::shared_ptr<Statement> > mStatements;

    // Semantic.
    std::shared_ptr<Scope> mScope;
};


/** Class **/
class Class : public Statement, public std::enable_shared_from_this<Class>
{
public:
    inline Class(std::shared_ptr<Name> name, std::shared_ptr<Block> block) :
        mName(name), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Name> mName;
    std::shared_ptr<Block> mBlock;
};


/** Concept **/
class Concept : public Statement
{
public:
    inline Concept(std::shared_ptr<Name> name, std::shared_ptr<Block> block) :
        mName(name), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Name> mName;
    std::shared_ptr<Block> mBlock;
};


/** Function **/
class Function : public Statement, public std::enable_shared_from_this<Function>
{
public:
    inline Function(std::shared_ptr<Signature> signature, std::shared_ptr<Block> block) :
        mSignature(signature), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Signature> mSignature;
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
    inline For(std::shared_ptr<Identify> variable, std::shared_ptr<Expression> range, std::shared_ptr<Block> block) :
        mVariable(variable), mRange(range), mBlock(block) {}

    void accept(Visitor& v);

    std::shared_ptr<Identify> mVariable;
    std::shared_ptr<Expression> mRange;
    std::shared_ptr<Block> mBlock;
};


/** If **/
class If : public Statement
{
public:
    If() = default;
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
    Switch() = default;
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
    Match() = default;

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
