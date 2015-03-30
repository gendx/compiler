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

#ifndef TYPE_HPP
#define TYPE_HPP

#include <memory>
#include <vector>
#include "../parse/token.hpp"

class Class;

class Type
{
    friend std::ostream& operator<<(std::ostream& out, const Type& type);

public:
    Type(std::weak_ptr<Class> definition) :
        mDefinition(definition) {}
    Type(std::weak_ptr<Class> definition, const std::vector<Type>& parameters) :
        mDefinition(definition), mParameters(parameters) {}

    bool operator<(const Type& rhs) const;

    inline std::weak_ptr<Class> definition() const;
    inline const std::vector<Type>& parameters() const;

private:
    std::weak_ptr<Class> mDefinition;
    std::vector<Type> mParameters;
};


inline std::weak_ptr<Class> Type::definition() const
    {return mDefinition;}
inline const std::vector<Type>& Type::parameters() const
    {return mParameters;}

#endif // TYPE_HPP
