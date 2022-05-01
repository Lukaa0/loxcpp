#include "Statement.h"
using namespace LoxCpp;

VarStatement::VarStatement(Token name, std::unique_ptr<Expression> expression) : expression(std::move(expression)), name(name)
{
}