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

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <vector>
#include "../parse/token.hpp"
#include "decoration.hpp"

class Visitor;

/** Expression **/
class Expression : public Token
{
public:
    virtual ~Expression();

    virtual void accept(Visitor& v) = 0;

protected:
    using Token::Token;
};


/** LexicalError **/
class LexicalError : public Expression
{
public:
    inline LexicalError(const Token& t) :
        Expression{t} {}

    void accept(Visitor& v);
};


/** ExprList **/
class ExprList : public Expression
{
public:
    ExprList() = default;
    inline ExprList(std::shared_ptr<Expression> e) :
        Expression{*e}, mExpressions{e} {}

    inline void append(std::shared_ptr<Expression> e)
        {appendToken(*e); mExpressions.push_back(e);}

    void accept(Visitor& v);

    std::vector<std::shared_ptr<Expression> > mExpressions;
};


/** Identifier **/
class Identifier : public Expression
{
public:
    inline Identifier(const Token& name) :
        Expression{name} {}

    void accept(Visitor& v);

    // Semantic.
    std::shared_ptr<Decoration> mDecoration;
};


/** Data **/
class Data : public Expression
{
public:
    inline Data(const Token& value) :
        Expression{value} {}

    void accept(Visitor& v);
};


class DataString : public Data
{
public:
    inline DataString(const Token& value) :
        Data(value) {}

    void accept(Visitor& v);
};

class DataChar : public Data
{
public:
    inline DataChar(const Token& value) :
        Data(value) {}

    void accept(Visitor& v);
};

class DataNumber : public Data
{
public:
    inline DataNumber(const Token& value) :
        Data(value) {}

    void accept(Visitor& v);
};


/** Identify **/
class Identify : public Expression, public std::enable_shared_from_this<Identify>
{
public:
    inline Identify(std::shared_ptr<Expression> type, std::shared_ptr<Identifier> identifier) :
        Expression{*type, *identifier}, mType(type), mIdentifier(identifier) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mType;
    std::shared_ptr<Identifier> mIdentifier;
};


/** Call **/
class Call : public Expression
{
public:
    inline Call(std::shared_ptr<Expression> expr, std::shared_ptr<ExprList> args) :
        Expression{*expr, *args}, mExpression(expr), mArgs(args) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
    std::shared_ptr<ExprList> mArgs;
};


/** Member **/
class Member : public Expression
{
public:
    inline Member(std::shared_ptr<Expression> expression, std::shared_ptr<Identifier> member) :
        Expression{*expression, *member}, mExpression(expression), mMember(member) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
    std::shared_ptr<Identifier> mMember;
};


/** Name **/
class Name : public Expression
{
public:
    inline Name(std::shared_ptr<Identifier> name) :
        Expression{*name}, mName(name) {}
    inline Name(std::shared_ptr<Identifier> name, std::shared_ptr<ExprList> args) :
        Expression{*name, *args}, mName(name), mArgs(args) {}

    void accept(Visitor& v);

    std::shared_ptr<Identifier> mName;
    std::shared_ptr<ExprList> mArgs;
};


/** Signature **/
class Signature : public Expression
{
public:
    inline Signature(std::shared_ptr<Expression> type, std::shared_ptr<Identifier> identifier, std::shared_ptr<ExprList> args) :
        Expression{*type, *identifier, *args}, mType(type), mIdentifier(identifier), mArgs(args) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mType;
    std::shared_ptr<Identifier> mIdentifier;
    std::shared_ptr<ExprList> mArgs;
};


/** Index **/
class Index : public Expression
{
public:
    inline Index(std::shared_ptr<Expression> expr, std::shared_ptr<ExprList> args) :
        Expression{*expr, *args}, mExpression(expr), mArgs(args) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
    std::shared_ptr<ExprList> mArgs;
};


/** Unary **/
class Unary : public Expression
{
public:
    enum UnOp {
        op_neg, op_not,
        op_plus, op_minus,
        op_incr, op_decr
    };

    inline Unary(const Token& op, std::shared_ptr<Expression> expr) :
        Expression{op, *expr}, mArg(expr), mOperator(strToOp(op.token())) {}

    void accept(Visitor& v);

    static UnOp strToOp(const std::string& s);
    static const std::string& opToStr(UnOp op);

    std::shared_ptr<Expression> mArg;
    UnOp mOperator;
};


/** Binary **/
class Binary : public Expression
{
public:
    enum BinOp {
        op_range,
        op_cond_or, op_cond_and,
        op_pow,
        op_mul, op_div, op_rem,
        op_add, op_sub,
        op_shl, op_shr,
        op_and, op_xor, op_or,
        op_lt, op_gt, op_eq, op_le, op_ge, op_ne,

        op_pow_eq,
        op_mul_eq, op_div_eq, op_rem_eq,
        op_add_eq, op_sub_eq,
        op_shl_eq, op_shr_eq,
        op_and_eq, op_xor_eq, op_or_eq,

        op_assign
    };

    inline Binary(std::shared_ptr<Expression> lhs, const Token& op, std::shared_ptr<Expression> rhs) :
        Expression{*lhs, op, *rhs}, mLhs(lhs), mRhs(rhs), mOperator(strToOp(op.token())) {}

    void accept(Visitor& v);

    static BinOp strToOp(const std::string& s);
    static const std::string& opToStr(BinOp op);

    std::shared_ptr<Expression> mLhs;
    std::shared_ptr<Expression> mRhs;
    BinOp mOperator;
};

#endif // EXPRESSION_HPP
