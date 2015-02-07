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

#include "scope.hpp"

Scope::Scope(std::shared_ptr<Scope> parent) :
    mParent(parent)
{
}


std::shared_ptr<Decoration> Scope::lookup(const std::string& name) const
{
    {
        auto it = mClasses.find(name);
        if (it != mClasses.end())
            return std::make_shared<DecorationType>(Type(it->second));
    }
    {
        auto it = mFunctions.find(name);
        if (it != mFunctions.end())
            return std::make_shared<DecorationFunction>(Type(std::weak_ptr<Class>()), it->second);
    }
    {
        auto it = mVariables.find(name);
        if (it != mVariables.end())
            return std::make_shared<DecorationVariable>(Type(std::weak_ptr<Class>()));
    }

    if (mParent)
        return mParent->lookup(name);

    return std::shared_ptr<Decoration>();
}

void Scope::set(const std::string& name, std::weak_ptr<Class> c)
{
    mClasses[name] = c;
}

void Scope::set(const std::string& name, std::weak_ptr<Function> f)
{
    mFunctions[name] = f;
}

void Scope::set(const std::string& name, std::weak_ptr<Identify> i)
{
    mVariables[name] = i;
}
