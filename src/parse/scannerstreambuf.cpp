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

#include "scannerstreambuf.hpp"

int ScannerStreambuf::underflow()
{
    if (mColumn == mLine.length())
    {
        mLastLine = mSharedLine;

        if (!std::getline(mIn, mLine))
        {
            mSharedLine = std::make_shared<std::string>(" ");
            return std::char_traits<char>::eof();
        }

        mSharedLine = std::make_shared<std::string>(mLine);
        *mSharedLine += ' ';

        mLine += '\n';
        mColumn = 0;
    }

    mChar = mLine[mColumn++];
    setg(&mChar, &mChar, &mChar + 1);
    return std::char_traits<char>::to_int_type(*gptr());
}


Token ScannerStreambuf::makeToken(const std::string& token, int lineNr) const
{
    std::shared_ptr<std::string> line = mSharedLine;
    --lineNr;
    int column = mColumn - 1;

    if (column == 0)
    {
        line = mLastLine;
        --lineNr;
        column = mLastLine->size();
    }

    return Token(token, line, lineNr, column);
}

Token ScannerStreambuf::makeToken(unsigned int size, int lineNr) const
{
    return Token(mSharedLine->substr(0, size), mSharedLine, lineNr - 1, size);
}

Token ScannerStreambuf::makeEOLToken(int lineNr) const
{
    return Token(mLastLine->substr(mLastLine->size() - 1), mLastLine, lineNr - 2, mLastLine->size());
}
