#include <memory>
#include "../Token/Token.h"
#include "Expression.h"
using namespace LoxCpp;


AssignExpression::AssignExpression(Token name, std::unique_ptr<Expression> value) : name(name), value(std::move(value))
{
}
