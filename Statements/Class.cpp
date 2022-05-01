#include "Statement.h"
using namespace LoxCpp;

Class::Class(Token name, std::unique_ptr<Expression> super, std::vector<std::unique_ptr<Function>> methods) : name(name), super(std::move(super)), methods(std::move(methods))
{
}