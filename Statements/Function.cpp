#include "Statement.h"
using namespace LoxCpp;

Function::Function(Token name, std::vector<Token> parameters, std::unique_ptr<Block> statements) : name(name), parameters(parameters), statements(std::move(statements))
{
}