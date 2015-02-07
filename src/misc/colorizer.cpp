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

#include "colorizer.hpp"

Colorizer::operator std::string() const
{
    if (!mStatus.empty())
        return std::string("\033[") + mStatus + "m";
    return std::string();
}

std::ostream& operator<<(std::ostream& out, const Colorizer& c)
{
    return out << (std::string)c;
}


Colorizer& Colorizer::rst()
{
    append("0");
    return *this;
}

Colorizer& Colorizer::bold()
{
    append("1");
    return *this;
}

Colorizer& Colorizer::dim()
{
    append("2");
    return *this;
}

Colorizer& Colorizer::italic()
{
    append("3");
    return *this;
}

Colorizer& Colorizer::under()
{
    append("4");
    return *this;
}

Colorizer& Colorizer::over()
{
    append("53");
    return *this;
}

Colorizer& Colorizer::blink()
{
    append("5");
    return *this;
}

Colorizer& Colorizer::neg()
{
    append("7");
    return *this;
}

Colorizer& Colorizer::hide()
{
    append("8");
    return *this;
}

Colorizer& Colorizer::fg(Colorizer::Color c)
{
    append(std::string("3") + colorChar(c));
    return *this;
}

Colorizer& Colorizer::bg(Colorizer::Color c)
{
    append(std::string("4") + colorChar(c));
    return *this;
}


std::string Colorizer::colorChar(Color c)
{
    switch (c)
    {
    case black:
        return "0";
    case red:
        return "1";
    case green:
        return "2";
    case yellow:
        return "3";
    case blue:
        return "4";
    case purple:
        return "5";
    case cyan:
        return "6";
    case white:
        return "7";
    default:
        return "9";
    }
}

void Colorizer::append(const std::string& modifier)
{
    if (mActive)
    {
        if (mStatus.empty())
            mStatus = modifier;
        else
        {
            mStatus += ";";
            mStatus += modifier;
        }
    }
}
