CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

PROJECT(compiler)

INCLUDE_DIRECTORIES(src)
ADD_EXECUTABLE(
    compiler
    src/main.cpp
    src/ast/ast.cpp
    src/ast/decoration.cpp
    src/ast/error/error.cpp
    src/ast/expression.cpp
    src/ast/scope.cpp
    src/ast/statement.cpp
    src/ast/syntaxerror.cpp
    src/ast/type.cpp
    src/ast/visit/classvisitor.cpp
    src/ast/visit/emptyvisitor.cpp
    src/ast/visit/errorvisitor.cpp
    src/ast/visit/functionvisitor.cpp
    src/ast/visit/printcode.cpp
    src/ast/visit/printvisitor.cpp
    src/ast/visit/recursivevisitor.cpp
    src/ast/visit/scopevisitor.cpp
    src/ast/visit/symbolresolver.cpp
    src/ast/visit/typevisitor.cpp
    src/ast/visit/variablevisitor.cpp
    src/ast/visit/visitor.cpp
    src/misc/colorizer.cpp
    src/parse/concatstream.cpp
    src/parse/lex.cc
    src/parse/parse.cc
    src/parse/scannerstreambuf.cpp
    src/parse/token.cpp
)

