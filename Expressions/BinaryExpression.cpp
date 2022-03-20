#include <memory>
#include "../Token/Token.h"
#include "Expression.h"
using namespace LoxCpp;


BinaryExpression::BinaryExpression(std::unique_ptr<Expression> left, Token& op, std::unique_ptr<Expression> right) :op(op)
{
	this->left = std::move(left);
	this->right = std::move(right);
}
