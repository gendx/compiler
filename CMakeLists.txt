CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

PROJECT(compiler)

INCLUDE_DIRECTORIES(src)
ADD_EXECUTABLE(
    compiler
    src/main.cpp
    src/ast/ast.cpp
    src/ast/decoration.cpp
    src/ast/expression.cpp
    src/ast/printcode.cpp
    src/ast/printvisitor.cpp
    src/ast/recursivevisitor.cpp
    src/ast/scope.cpp
    src/ast/scopevisitor.cpp
    src/ast/statement.cpp
    src/ast/syntaxerror.cpp
    src/ast/visitor.cpp
    src/misc/colorizer.cpp
    src/parse/concatstream.cpp
    src/parse/lex.cc
    src/parse/parse.cc
    src/parse/scannerstreambuf.cpp
    src/parse/token.cpp
)

