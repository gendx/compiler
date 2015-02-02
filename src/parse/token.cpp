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

#include "token.hpp"

std::ostream& operator<<(std::ostream& out, const Token& token)
{
    out << " line " << token.mLineNr << ":" << token.mColumnStart + 1 << std::endl;
    out << *token.mLine << std::endl;

    for (int i = 0 ; i < token.mColumnStart ; ++i)
        out << ".";
    for (int i = token.mColumnStart ; i < token.mColumnEnd ; ++i)
        out << "^";
    for (int i = token.mColumnEnd ; i < token.mLine->size() ; ++i)
        out << ".";
    return out << std::endl;
}


Token::Token(std::initializer_list<Token> tokens) :
    Token()
{
    for (const Token& t : tokens)
    {
        if (!t)
            continue;

        if (!*this)
        {
            mLine = t.mLine;
            mLineNr = t.mLineNr;
            mColumnStart = t.mColumnStart;
            mColumnEnd = t.mColumnEnd;
        }
        else if (t.mColumnEnd > mColumnEnd)
            mColumnEnd = t.mColumnEnd;
    }

    mToken = mLine->substr(mColumnStart, mColumnEnd - mColumnStart);
}

void Token::appendToken(const Token& other)
{
    if (other)
    {
        if (!*this)
            *this = other;
        else if (other.mColumnEnd > mColumnEnd)
        {
            mColumnEnd = other.mColumnEnd;
            mToken = mLine->substr(mColumnStart, mColumnEnd - mColumnStart);
        }
    }
}
