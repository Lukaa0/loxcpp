#include "Expression.h"
using namespace LoxCpp;
GroupingExpression::GroupingExpression(std::unique_ptr<Expression> expression) : expression(std::move(expression))
{
}