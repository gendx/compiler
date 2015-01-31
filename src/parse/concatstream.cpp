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

#include "concatstream.hpp"

int ConcatStreamBuf::underflow()
{
    if (gptr() == egptr())
    {
        std::streamsize size = 0;
        while (mCurrentBuf < 2)
        {
            size = mStreamBufs[mCurrentBuf]->sgetn(mCharBuf, sizeof mCharBuf);
            if (!size)
                mCurrentBuf++;
            else
                break;
        }
        setg(mCharBuf, mCharBuf, mCharBuf + size);
    }

    return gptr() == egptr()
         ? std::char_traits<char>::eof()
         : std::char_traits<char>::to_int_type(*gptr());
}


PrependIstream::PrependIstream(std::istream& in, const std::string& prepend) :
    std::istream(&mBuf),
    mPrepend(prepend),
    mBuf(mPrepend, in)
{
}
