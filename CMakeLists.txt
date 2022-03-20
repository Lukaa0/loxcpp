# CMakeList.txt : CMake project for Lox++, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Lox "Lox.cpp" "Lox.h" "Token/Token.h" "Token/Token.cpp" "Scanner/Scanner.h" "Scanner/Scanner.cpp" "Parser/Parser.h" "Parser/Parser.cpp" "Expressions/Expression.h" "Expressions/BinaryExpression.cpp"   "Expressions/UnaryExpression.cpp")

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)
