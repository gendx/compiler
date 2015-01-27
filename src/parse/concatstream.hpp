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

#ifndef CONCATSTREAM_HPP
#define CONCATSTREAM_HPP

#include <iostream>
#include <sstream>

class ConcatStreamBuf : public std::streambuf
{
public:
    inline ConcatStreamBuf(std::istream& sbuf1, std::istream& sbuf2);

    int underflow();

private:
    int useBuf;
    std::streambuf* sbuf_[2];
    char buffer_[1024];
};

inline ConcatStreamBuf::ConcatStreamBuf(std::istream& sbuf1, std::istream& sbuf2) :
    useBuf(0), sbuf_{sbuf1.rdbuf(), sbuf2.rdbuf()}
{
}


class PrependIstream : public std::istream
{
public:
    PrependIstream(std::istream& in, const std::string& prepend);

private:
    std::istringstream mPrepend;
    ConcatStreamBuf mBuf;
};

#endif // CONCATSTREAM_HPP
