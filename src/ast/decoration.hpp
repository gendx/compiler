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

class Function;
class Visitor;

// A decoration specifies what an identifier represents (type, function or variable).
class Decoration
{
public:
    virtual ~Decoration();

    virtual void accept(Visitor& v) = 0;

protected:
    inline Decoration(Type type) :
        mType(type) {}

    Type mType;
};


class DecorationType : public Decoration
{
public:
    inline DecorationType(Type type) :
        Decoration(type) {}

    void accept(Visitor& v);
};

class DecorationFunction : public Decoration
{
public:
    inline DecorationFunction(Type type, std::weak_ptr<Function> function) :
        Decoration(type), mFunction(function) {}

    void accept(Visitor& v);

private:
    std::weak_ptr<Function> mFunction;
};

class DecorationVariable : public Decoration
{
public:
    inline DecorationVariable(Type type) :
        Decoration(type) {}

    void accept(Visitor& v);
};

#endif // DECORATION_HPP
