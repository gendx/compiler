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

#ifndef ERROR_HPP
#define ERROR_HPP

#include "../../parse/token.hpp"
#include <iostream>

namespace error {

class Error
{
public:
    virtual ~Error() = default;
    virtual std::ostream& print(std::ostream& out) = 0;
};

/** AlreadyDeclared **/
class AlreadyDeclared : public Error
{
public:
    inline AlreadyDeclared(const Token& error, const Token& first);

    std::ostream& print(std::ostream& out);

private:
    Token mError;
    Token mFirst;
};

inline AlreadyDeclared::AlreadyDeclared(const Token& error, const Token& first) :
    mError(error), mFirst(first) {}


/** ExpectedType **/
class ExpectedType : public Error
{
public:
    inline ExpectedType(const Token& error);

    std::ostream& print(std::ostream& out);

private:
    Token mError;
};

inline ExpectedType::ExpectedType(const Token& error) :
    mError(error) {}


/** AlreadyQualifiedType **/
class AlreadyQualifiedType : public Error
{
public:
    inline AlreadyQualifiedType(const Token& type, const Token& extraQualification);

    std::ostream& print(std::ostream& out);

private:
    Token mType;
    Token mExtraQualification;
};

inline AlreadyQualifiedType::AlreadyQualifiedType(const Token& type, const Token& extraQualification) :
    mType(type), mExtraQualification(extraQualification) {}


/** EmptyTypeQualification **/
class EmptyTypeQualification : public Error
{
public:
    inline EmptyTypeQualification(const Token& error);

    std::ostream& print(std::ostream& out);

private:
    Token mError;
};

inline EmptyTypeQualification::EmptyTypeQualification(const Token& error) :
    mError(error) {}

}

#endif // ERROR_HPP
