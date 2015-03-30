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

#include "type.hpp"

#include "statement.hpp"

std::ostream& operator<<(std::ostream& out, const Type& type)
{
    out << type.mDefinition.lock()->mName->mName->token();
    if (!type.mParameters.empty())
    {
        out << "[";
        bool started = false;
        for (auto&& t : type.mParameters)
        {
            if (started)
                out << ", ";
            started = true;
            out << t;
        }
        out << "]";
    }
    return out;
}

bool Type::operator<(const Type& rhs) const
{
    auto lhsp = mDefinition.lock().get();
    auto rhsp = rhs.mDefinition.lock().get();
    return lhsp != rhsp ?
                lhsp < rhsp :
                mParameters < rhs.mParameters;
}
