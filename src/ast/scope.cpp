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


std::shared_ptr<DecorationIdentifier> Scope::lookup(const std::string& name) const
{
    std::shared_ptr<DecorationIdentifier> result = this->lookupLocal(name);

    if ((!result) && mParent)
        return mParent->lookup(name);

    return result;
}

std::shared_ptr<DecorationIdentifier> Scope::lookupLocal(const std::string& name) const
{
    {
        auto it = mClasses.find(name);
        if (it != mClasses.end())
            return it->second;
    }
    {
        auto it = mFunctions.find(name);
        if (it != mFunctions.end())
            return it->second.front();
    }
    {
        auto it = mVariables.find(name);
        if (it != mVariables.end())
            return it->second;
    }

    return std::shared_ptr<DecorationIdentifier>();
}


std::shared_ptr<DecorationType> Scope::set(const std::string& name, std::weak_ptr<Class> c)
{
    auto decoration = std::make_shared<DecorationType>(c);
    mClasses[name] = decoration;
    return decoration;
}

std::shared_ptr<DecorationFunction> Scope::set(const std::string& name, std::weak_ptr<Function> f)
{
    auto decoration = std::make_shared<DecorationFunction>(f);

    auto found = mFunctions.find(name);
    if (found != mFunctions.end())
        found->second.push_back(decoration);
    else
        mFunctions[name].push_back(decoration);

    return decoration;
}

std::shared_ptr<DecorationVariable> Scope::set(const std::string& name, std::weak_ptr<Identify> i)
{
    auto decoration = std::make_shared<DecorationVariable>(i);
    mVariables[name] = decoration;
    return decoration;
}
