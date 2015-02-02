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

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <memory>
#include <iostream>
#include <initializer_list>

class Token
{
    friend std::ostream& operator<<(std::ostream& out, const Token& token);

public:
    inline Token();
    inline Token(const std::string& token, std::shared_ptr<std::string> line, int lineNr, int column);

    inline operator bool() const;
    inline const std::string token() const;

    void appendToken(const Token& other);

protected:
    Token(std::initializer_list<Token> tokens);

private:
    std::string mToken;

    std::shared_ptr<std::string> mLine;
    int mLineNr;
    int mColumnStart;
    int mColumnEnd;
};

inline Token::Token() :
    mLineNr(0), mColumnStart(0), mColumnEnd(0) {}
inline Token::Token(const std::string& token, std::shared_ptr<std::string> line, int lineNr, int column) :
    mToken(token), mLine(line), mLineNr(lineNr), mColumnStart(column - token.size()), mColumnEnd(column) {}

inline Token::operator bool() const
    {return (bool)mLine;}
inline const std::string Token::token() const
    {return mToken;}

#endif // TOKEN_HPP
