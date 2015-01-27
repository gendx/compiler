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
    if (this->gptr() == this->egptr())
    {
        std::streamsize size = 0;
        while (useBuf < 2)
        {
            size = this->sbuf_[useBuf]->sgetn(this->buffer_, sizeof this->buffer_);
            if (!size)
                useBuf++;
            else
                break;
        }
        this->setg(this->buffer_, this->buffer_, this->buffer_ + size);
    }

    return this->gptr() == this->egptr()
         ? std::char_traits<char>::eof()
         : std::char_traits<char>::to_int_type(*this->gptr());
}


PrependIstream::PrependIstream(std::istream& in, const std::string& prepend) :
    std::istream(&mBuf),
    mPrepend(prepend),
    mBuf(mPrepend, in)
{
}
