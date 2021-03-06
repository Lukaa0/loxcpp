﻿# CMakeList.txt : CMake project for Lox++, include source and define
# project specific logic here.
#

include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

cmake_minimum_required (VERSION 3.8)

include_directories(${GTEST_INCLUDE_DIRS})

link_libraries(${GTEST_LIBRARIES} gtest_main)

cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Lox "Lox.cpp" "Lox.h" "Token/Token.h" "Token/Token.cpp" "Scanner/Scanner.h" "Scanner/Scanner.cpp" "Parser/Parser.h" "Parser/Parser.cpp" "Expressions/Expression.h" "Expressions/BinaryExpression.cpp"   "Expressions/UnaryExpression.cpp" "Expressions/LiteralExpression.cpp" "Expressions/GroupingExpression.cpp" "Token/Literal.h" "Models/ErrorModel.h"  "Models/ErrorModel.cpp" "Models/LoxException.h" "Models/LoxException.cpp" "AST/AstGenerator.h" "AST/AstGenerator.cpp" "Utils/StringUtils.cpp" "Utils/StringUtils.h" "test/src/generate_ast_tests.cpp" "Interpreter/Interpreter.h" "Interpreter/Interpreter.cpp" "test/src/interpreter_expression_tests.cpp" "Statements/Statement.h" "Statements/Block.cpp" "Statements/ExpressionStatement.cpp" "Statements/Print.cpp" "Statements/VarStatement.cpp" "Expressions/VarExpression.cpp" "Environment/Environment.h" "Expressions/AssignExpression.cpp" "Environment/Environment.cpp")

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
endif(MSVC)
