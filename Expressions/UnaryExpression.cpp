#include "Expression.h"
#include <memory>
using namespace LoxCpp;

UnaryExpression::UnaryExpression(Token & op, std::unique_ptr<Expression> right) : op(op), right(std::move(right))
{

}
