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

#ifndef AST_HPP
#define AST_HPP

#include "statement.hpp"
#include "syntaxerror.hpp"

class AST
{
public:
    AST();
    AST(std::shared_ptr<Block> root);

    void visit(Visitor& v);

    inline void setSyntaxError(const Token& token, int state);
    inline void setErrorSymbol(const std::string& symbol);
    inline void addErrorExpectedSymbol(const std::string& symbol);

    bool printErrors(std::ostream& out) const;

private:
    std::shared_ptr<Block> mRoot;
    std::shared_ptr<SyntaxError> mSyntaxError;
};

inline void AST::setSyntaxError(const Token& token, int state)
    {mSyntaxError = std::make_shared<SyntaxError>(token, state);}
inline void AST::setErrorSymbol(const std::string& symbol)
    {mSyntaxError->setSymbol(symbol);}
inline void AST::addErrorExpectedSymbol(const std::string& symbol)
    {mSyntaxError->addExpectedSymbol(symbol);}

#endif // AST_HPP
