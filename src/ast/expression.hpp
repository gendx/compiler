#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <memory>
#include <vector>
#include <string>

class Visitor;

/** Expression **/
class Expression
{
public:
    virtual ~Expression();

    virtual void accept(Visitor& v) = 0;
};


/** ExprList **/
class ExprList : public Expression
{
public:
    inline ExprList()
        {}
    inline ExprList(std::shared_ptr<Expression> e) :
        mExpressions{e} {}

    inline void append(std::shared_ptr<Expression> e)
        {mExpressions.push_back(e);}

    void accept(Visitor& v);

    std::vector<std::shared_ptr<Expression> > mExpressions;
};


/** Identifier **/
class Identifier : public Expression
{
public:
    inline Identifier(const std::string& name) :
        mName(name) {}

    void accept(Visitor& v);

    std::string mName;
};


/** Data **/
class Data : public Expression
{
public:
    inline Data(const std::string& value) :
        mValue(value) {}

    void accept(Visitor& v);

    std::string mValue;
};


class DataString : public Data
{
public:
    inline DataString(const std::string& value) :
        Data(value) {}

    void accept(Visitor& v);
};

class DataChar : public Data
{
public:
    inline DataChar(const std::string& value) :
        Data(value) {}

    void accept(Visitor& v);
};

class DataNumber : public Data
{
public:
    inline DataNumber(const std::string& value) :
        Data(value) {}

    void accept(Visitor& v);
};


/** Identify **/
class Identify : public Expression
{
public:
    inline Identify(std::shared_ptr<Expression> type, std::shared_ptr<Identifier> identifier) :
        mType(type), mIdentifier(identifier) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mType;
    std::shared_ptr<Identifier> mIdentifier;
};


/** Call **/
class Call : public Expression
{
public:
    inline Call(std::shared_ptr<Identifier> identifier, std::shared_ptr<ExprList> args) :
        mIdentifier(identifier), mArgs(args) {}

    void accept(Visitor& v);

    std::shared_ptr<Identifier> mIdentifier;
    std::shared_ptr<ExprList> mArgs;
};


/** Member **/
class Member : public Expression
{
public:
    inline Member(std::shared_ptr<Expression> expression, std::shared_ptr<Identifier> member) :
        mExpression(expression), mMember(member) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
    std::shared_ptr<Identifier> mMember;
};


/** Method **/
class Method : public Expression
{
public:
    inline Method(std::shared_ptr<Expression> expression, std::shared_ptr<Call> method) :
        mExpression(expression), mMethod(method) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mExpression;
    std::shared_ptr<Call> mMethod;
};


/** Signature **/
class Signature : public Expression
{
public:
    inline Signature(std::shared_ptr<Expression> type, std::shared_ptr<Call> call) :
        mType(type), mCall(call) {}

    void accept(Visitor& v);

    std::shared_ptr<Expression> mType;
    std::shared_ptr<Call> mCall;
};


/** Index **/
class Index : public Expression
{
public:
    inline Index(std::shared_ptr<Expression> expr, std::shared_ptr<ExprList> args) :
        mExpression(expr), mArgs(args) {}

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
        op_plus, op_minus
    };

    inline Unary(const std::string& op, std::shared_ptr<Expression> expr) :
        mArg(expr), mOperator(strToOp(op)) {}

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

    inline Binary(std::shared_ptr<Expression> lhs, const std::string& op, std::shared_ptr<Expression> rhs) :
        mLhs(lhs), mRhs(rhs), mOperator(strToOp(op)) {}

    void accept(Visitor& v);

    static BinOp strToOp(const std::string& s);
    static const std::string& opToStr(BinOp op);

    std::shared_ptr<Expression> mLhs;
    std::shared_ptr<Expression> mRhs;
    BinOp mOperator;
};

#endif // EXPRESSION_HPP
