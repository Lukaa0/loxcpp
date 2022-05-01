#include "Statement.h"
using namespace LoxCpp;

Block::Block(std::vector<std::unique_ptr<Statement>> statements) :statements(std::move(statements))
{
}