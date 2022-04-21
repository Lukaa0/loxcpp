#include "Interpreter.h"
#include "../Lox.h"
using namespace LoxCpp;

Interpreter::Interpreter(ErrorHandler& errorHandler) : errorHandler(errorHandler)
{
}

std::any Interpreter::VisitBinary(BinaryExpression& expression)
{
	auto right = expression.right->Accept(*this);
	auto left = expression.left->Accept(*this);
	switch (expression.op.type) {
	case TokenType::MINUS: {
		if (checkNumberOperands(expression.op, left, right))
			return std::any_cast<double>(left) - std::any_cast<double>(right);
	}
	case TokenType::SLASH: {
		if (checkNumberOperands(expression.op, left, right))
			return std::any_cast<double>(left) / std::any_cast<double>(right);
	}
	case TokenType::STAR: {
		if (checkNumberOperands(expression.op, left, right))
			return std::any_cast<double>(left) * std::any_cast<double>(right);
	}
	case TokenType::PLUS: {
		if (left.type() == typeid(double) && right.type() == typeid(double)) {
			if (checkNumberOperands(expression.op, left, right))
				return std::any_cast<double>(left) + std::any_cast<double>(right);
		}
		if (left.type() == typeid(std::string) && right.type() == typeid(std::string)) {
			return std::any_cast<std::string>(left) + std::any_cast<std::string>(right);
		}
		this->errorHandler.Add("Operand must either be numbers or strings", expression.op.line);
		return nullptr;

	}
	case TokenType::GREATER: {
		if (checkNumberOperands(expression.op, left, right))
			return std::any_cast<double>(left) > std::any_cast<double>(right);
	}
	case TokenType::GREATER_EQUAL: {
		if (checkNumberOperands(expression.op, left, right))
			return std::any_cast<double>(left) >= std::any_cast<double>(right);
	}
	case TokenType::LESS: {
		if (checkNumberOperands(expression.op, left, right))
			return std::any_cast<double>(left) < std::any_cast<double>(right);
	}
	case TokenType::LESS_EQUAL: {
		if (checkNumberOperands(expression.op, left, right))
			return std::any_cast<double>(left) <= std::any_cast<double>(right);
	}
	default:
		this->errorHandler.Add("Invalid Expression", expression.op.line);
	}
	return nullptr;
}

std::any Interpreter::VisitUnary(UnaryExpression& expression)
{
	std::any right = expression.right->Accept(*this);

	switch (expression.op.type) {
	case TokenType::MINUS: {
		if (this->checkNumberOperand(expression.op, right)) {
			double rightFlt = std::any_cast<double>(right);
			return -rightFlt;
		}
	}
	case TokenType::BANG: {
		if (!right.has_value()) return false;
		if (right.type() == typeid(bool)) return std::any_cast<bool>(right);
		return true;
	}
	}

	return nullptr;
}

std::any Interpreter::VisitLiteral(LiteralExpression& expression)
{
	return expression.literal;
}

std::any Interpreter::VisitGrouping(GroupingExpression& expression)
{
	return expression.expression->Accept(*this);
}

void Interpreter::Interpret(std::unique_ptr<Expression> expression)
{
	std::any value = expression->Accept(*this);
	if (this->errorHandler.HasError) {
		Error(this->errorHandler.Errors[0].Line, this->errorHandler.Errors[0].ErrorMessage);
	}
	else {
		try {
			this->Output = this->stringify(value);
			std::cout << this->Output;
		}
		catch (std::bad_any_cast) {
			//TODO: Refactor!
			this->errorHandler.Add("Invalid literal", 0);
			Error(this->errorHandler.Errors[0].Line, this->errorHandler.Errors[0].ErrorMessage);
		}
	}
}

std::string Interpreter::stringify(std::any object)
{
	if (!object.has_value()) return "null";
	if (object.type() == typeid(double)) {
		double doubleObj = std::any_cast<double>(object);
		std::string stringObj = std::to_string(doubleObj);
		//Remove trailing zeros
		stringObj.erase ( stringObj.find_last_not_of('0') + 1, std::string::npos );
		stringObj.erase ( stringObj.find_last_not_of('.') + 1, std::string::npos );
		return stringObj;

	}
	if (object.type() == typeid(bool)) {
		bool boolObj = std::any_cast<bool>(object);
		return boolObj ? std::string("true") : std::string("false");
	}
	return std::any_cast<std::string>(object);
}


bool Interpreter::checkNumberOperand(const Token& oper, const std::any& operand) {
	if (operand.type() == typeid(double)) return true;
	this->errorHandler.Add("Operand must be a number", oper.line);
	return false;
}

bool Interpreter::checkNumberOperands(const Token& oper, const std::any& left, const std::any& right) {
	if (left.type() == typeid(double) && right.type() == typeid(double)) return true;
	this->errorHandler.Add("Operand must be a number", oper.line);
	return false;
}
