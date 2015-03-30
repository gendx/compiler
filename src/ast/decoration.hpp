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

#ifndef DECORATION_HPP
#define DECORATION_HPP

#include "type.hpp"
#include "../parse/token.hpp"

class Visitor;
class Function;
class Identify;

// A decoration specifies what an expression represents (value, type, function or variable).
class Decoration
{
public:
    virtual ~Decoration();

    virtual void accept(Visitor& v) = 0;

    virtual bool isValue();
    virtual bool isIdentifier();
    virtual bool isType();
    virtual bool isFunction();
    virtual bool isVariable();

    std::shared_ptr<Type> mType;

protected:
    Decoration() = default;
    inline Decoration(std::shared_ptr<Type> type) :
        mType(type) {}
};


class DecorationValue : public Decoration
{
public:
    void accept(Visitor& v);

    virtual bool isValue();
};

class DecorationIdentifier : public Decoration
{
public:
    virtual const Token& token() const = 0;

    virtual bool isIdentifier();

protected:
    using Decoration::Decoration;
};


class DecorationType : public DecorationIdentifier
{
public:
    inline DecorationType(std::weak_ptr<Class> type) :
        DecorationIdentifier(std::make_shared<Type>(type)) {}
    inline DecorationType(std::weak_ptr<Class> type, const std::vector<Type>& arguments) :
        DecorationIdentifier(std::make_shared<Type>(type, arguments)) {}

    void accept(Visitor& v);
    const Token& token() const;

    virtual bool isType();
};

class DecorationFunction : public DecorationIdentifier
{
public:
    inline DecorationFunction(std::weak_ptr<Function> function) :
        mFunction(function) {}

    void accept(Visitor& v);
    const Token& token() const;

    virtual bool isFunction();

    std::weak_ptr<Function> mFunction;
};

class DecorationVariable : public DecorationIdentifier
{
public:
    inline DecorationVariable(std::weak_ptr<Identify> identify) :
        mIdentify(identify) {}

    void accept(Visitor& v);
    const Token& token() const;

    virtual bool isVariable();

    std::weak_ptr<Identify> mIdentify;
};

#endif // DECORATION_HPP
