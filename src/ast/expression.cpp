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

#include "expression.hpp"
#include "visitor.hpp"

#include <unordered_map>
#include <map>
#include <stdexcept>

Expression::~Expression()
{
}


Unary::UnOp Unary::strToOp(const std::string& s)
{
    static std::unordered_map<std::string, UnOp> m {{
            {"~", op_neg},
            {"!", op_not},
            {"+", op_plus},
            {"-", op_minus},
            {"++", op_incr},
            {"--", op_decr},
                                           }};

    auto found = m.find(s);
    if (found != m.end())
        return found->second;
    throw std::domain_error("Unexpected error : unknown unary operator");
}

const std::string& Unary::opToStr(Unary::UnOp op)
{
    static std::map<UnOp, std::string> m {{
            {op_neg, "~"},
            {op_not, "!"},
            {op_plus, "+"},
            {op_minus, "-"},
            {op_incr, "++"},
            {op_decr, "--"},
                                           }};

    auto&& found = m.find(op);
    if (found != m.end())
        return found->second;
    throw std::domain_error("Unexpected error : unknown unary operator");
}


Binary::BinOp Binary::strToOp(const std::string& s)
{
    static std::unordered_map<std::string, BinOp> m {{
            {"..", op_range},
            {"||", op_cond_or},
            {"&&", op_cond_and},
            {"**", op_pow},
            {"*", op_mul},
            {"/", op_div},
            {"%", op_rem},
            {"+", op_add},
            {"-", op_sub},
            {"<<", op_shl},
            {">>", op_shr},
            {"&", op_and},
            {"^", op_xor},
            {"|", op_or},
            {"<", op_lt},
            {">", op_gt},
            {"==", op_eq},
            {"<=", op_le},
            {">=", op_ge},
            {"!=", op_ne},
            {"**=", op_pow_eq},
            {"*=", op_mul_eq},
            {"/=", op_div_eq},
            {"%=", op_rem_eq},
            {"+=", op_add_eq},
            {"-=", op_sub_eq},
            {"<<=", op_shl_eq},
            {">>=", op_shr_eq},
            {"&=", op_and_eq},
            {"^=", op_xor_eq},
            {"|=", op_or_eq},
            {":=", op_assign},
                                           }};

    auto found = m.find(s);
    if (found != m.end())
        return found->second;
    throw std::domain_error("Unexpected error : unknown binary operator");
}

const std::string& Binary::opToStr(Binary::BinOp op)
{
    static std::map<BinOp, std::string> m {{
            {op_range, ".."},
            {op_cond_or, "||"},
            {op_cond_and, "&&"},
            {op_pow, "**"},
            {op_mul, "*"},
            {op_div, "/"},
            {op_rem, "%"},
            {op_add, "+"},
            {op_sub, "-"},
            {op_shl, "<<"},
            {op_shr, ">>"},
            {op_and, "&"},
            {op_xor, "^"},
            {op_or, "|"},
            {op_lt, "<"},
            {op_gt, ">"},
            {op_eq, "=="},
            {op_le, "<="},
            {op_ge, ">="},
            {op_ne, "!="},
            {op_pow_eq, "**="},
            {op_mul_eq, "*="},
            {op_div_eq, "/="},
            {op_rem_eq, "%="},
            {op_add_eq, "+="},
            {op_sub_eq, "-="},
            {op_shl_eq, "<<="},
            {op_shr_eq, ">>="},
            {op_and_eq, "&="},
            {op_xor_eq, "^="},
            {op_or_eq, "|="},
            {op_assign, ":="},
                                           }};

    auto&& found = m.find(op);
    if (found != m.end())
        return found->second;
    throw std::domain_error("Unexpected error : unknown binary operator");
}


void ExprList::accept(Visitor& v)
{
    v.visit(*this);
}
void Identifier::accept(Visitor& v)
{
    v.visit(*this);
}
void Data::accept(Visitor& v)
{
    v.visit(*this);
}
void DataString::accept(Visitor& v)
{
    v.visit(*this);
}
void DataChar::accept(Visitor& v)
{
    v.visit(*this);
}
void DataNumber::accept(Visitor& v)
{
    v.visit(*this);
}
void Identify::accept(Visitor& v)
{
    v.visit(*this);
}
void Call::accept(Visitor& v)
{
    v.visit(*this);
}
void Member::accept(Visitor& v)
{
    v.visit(*this);
}
void Method::accept(Visitor& v)
{
    v.visit(*this);
}
void Signature::accept(Visitor& v)
{
    v.visit(*this);
}
void Index::accept(Visitor& v)
{
    v.visit(*this);
}
void Unary::accept(Visitor& v)
{
    v.visit(*this);
}
void Binary::accept(Visitor& v)
{
    v.visit(*this);
}
