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

#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <unordered_map>
#include "decoration.hpp"

class Identify;

class Scope
{
public:
    Scope() = default;
    Scope(std::shared_ptr<Scope> parent);

    std::shared_ptr<Decoration> lookup(const std::string& name) const;
    void set(const std::string& name, std::weak_ptr<Class> c);
    void set(const std::string& name, std::weak_ptr<Function> f);
    void set(const std::string& name, std::weak_ptr<Identify> i);

private:
    std::shared_ptr<Scope> mParent;
    std::unordered_map<std::string, std::weak_ptr<Class> > mClasses;
    std::unordered_map<std::string, std::weak_ptr<Function> > mFunctions;
    std::unordered_map<std::string, std::weak_ptr<Identify> > mVariables;
};

#endif // SCOPE_HPP
