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

// Generated by Bisonc++ V4.08.01

#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "Parserbase.h"
// $insert scanner.h
#include "Scanner.h"

#include "concatstream.hpp"


#undef Parser
class Parser: public ParserBase
{
    PrependIstream mIstream;

    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        explicit Parser(std::istream &in = std::cin, std::ostream &out = std::cout);
    
        int parse();
        AST ast();

    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
        void exceptionHandler__(std::exception const &exc);

        AST mAst;
        int    d_token_lastError;
        size_t d_state_lastError;
};


inline AST Parser::ast()
{
    return mAst;
}


#endif
