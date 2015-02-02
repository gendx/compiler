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

#ifndef SCANNERSTREAMBUF_HPP
#define SCANNERSTREAMBUF_HPP

#include <iostream>
#include <memory>
#include "token.hpp"

class ScannerStreambuf : public std::streambuf
{
public:
    inline ScannerStreambuf(std::istream& in);

    int underflow();

    Token makeToken(const std::string& token, int lineNr) const;
    Token makeToken(unsigned int size, int lineNr) const;
    Token makeEOLToken(int lineNr) const;

private:
    std::istream& mIn;
    std::string mLine;
    std::shared_ptr<std::string> mSharedLine;
    std::shared_ptr<std::string> mLastLine;
    int mColumn;
    char mChar;
};

inline ScannerStreambuf::ScannerStreambuf(std::istream& in) :
    mIn(in), mSharedLine(std::make_shared<std::string>()), mColumn(0), mChar(0) {setg(nullptr, nullptr, nullptr);}

#endif // SCANNERSTREAMBUF_HPP
