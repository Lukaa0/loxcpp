#include "Statement.h"
using namespace LoxCpp;

ExpressionStatement::ExpressionStatement(std::unique_ptr<Expression> expression) : expression(std::move(expression))
{
}