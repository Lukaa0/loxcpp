#include "Statement.h"
using namespace LoxCpp;

Print::Print(std::unique_ptr<Expression> expression) : expression(std::move(expression))
{
}