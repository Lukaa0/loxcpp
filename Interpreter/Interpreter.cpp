#include "Interpreter.h"

#include <utility>
#include "../Lox.h"
using namespace LoxCpp;

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
		this->loxException.Add("Operand must either be numbers or strings", expression.op.line);
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
		this->loxException.Add("Invalid Expression", expression.op.line);
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

std::any Interpreter::VisitAssignExpression(AssignExpression& expression)
{
	auto value = expression.value->Accept(*this);
	this->environment.Assign(expression.name, value);
	return value;
}

std::any Interpreter::VisitVarExpression(VarExpression& expression)
{
	return this->environment.Get(expression.name);
}

std::any Interpreter::VisitExpressionStatement(ExpressionStatement& statement)
{
	auto value = statement.expression->Accept(*this);
	this->printOutput(value);
	return value;
}

std::any Interpreter::VisitPrint(Print& statement)
{
	auto value = statement.expression->Accept(*this);
	this->printOutput(value);
	return value;
}

std::any Interpreter::VisitBlock(Block& statement)
{
	return std::any();
}


std::any Interpreter::VisitClass(Class& statement)
{
	return std::any();
}

std::any Interpreter::VisitFunction(Function& statement)
{
	return std::any();
}

std::any Interpreter::VisitVarStatement(VarStatement& statement)
{
	std::any value = nullptr;
	if (statement.expression != nullptr)
	{
		value = statement.expression->Accept(*this);
	}
	environment.Define(statement.name.lexeme, value);
	return nullptr;
}


void Interpreter::Interpret(std::vector<std::unique_ptr<Statement>> statements)
{

	for (auto& statement : statements)
	{
		statement->Accept(*this);
	}

	//std::any value = expression->Accept(*this);
	//if (this->loxException.HasError) {
	//	Error(this->loxException.Errors[0].Line, this->loxException.Errors[0].ErrorMessage);
	//}
	//else {
	//	this->printOutput(value);
	//}
}

std::string Interpreter::stringify(std::any object)
{
	if (!object.has_value()) return "null";
	if (object.type() == typeid(double)) {
		double doubleObj = std::any_cast<double>(object);
		std::string stringObj = std::to_string(doubleObj);
		//Remove trailing zeros
		stringObj.erase(stringObj.find_last_not_of('0') + 1, std::string::npos);
		stringObj.erase(stringObj.find_last_not_of('.') + 1, std::string::npos);
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
	this->loxException.Add("Operand must be a number", oper.line);
	throw LoxException(loxException);
}

bool Interpreter::checkNumberOperands(const Token& oper, const std::any& left, const std::any& right) {
	if (left.type() == typeid(double) && right.type() == typeid(double)) return true;
	this->loxException.Add("Operand must be a number", oper.line);
	throw LoxException(loxException);
}

void Interpreter::printOutput(std::any value)
{
	try {
		this->Output = this->stringify(std::move(value));
		std::cout << this->Output;
	}
	catch (std::bad_any_cast) {
		//TODO: Refactor!
		this->loxException.Add("Invalid literal", 0);
		Error(this->loxException.Errors[0].Line, this->loxException.Errors[0].ErrorMessage);
	}
}

void Interpreter::executeBlock(std::vector<std::unique_ptr<Statement>> statements, Environment& env)
{
	auto prev = this->environment;

	this->environment = env;
	for (auto& statement : statements)
	{
		statement->Accept(*this);
	}

	this->environment = prev;
}
