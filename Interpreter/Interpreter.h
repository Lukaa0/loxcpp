#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../Expressions/Expression.h"
#include <iostream>
#include "../Models/ErrorHandler.h"
namespace LoxCpp{
	class Interpreter : ExpressionVisitor{
	public:
		Interpreter(ErrorHandler& errorHandler);
		std::any VisitBinary(BinaryExpression& expression) override;
		std::any VisitUnary(UnaryExpression& expression) override;
		std::any VisitLiteral(LiteralExpression& expression) override;
		std::any VisitGrouping(GroupingExpression& expression) override;
		void Interpret(std::unique_ptr<Expression> expression);
		std::string Output;
	private:
		std::string stringify(std::any object);
		bool checkNumberOperand(const Token& oper, const std::any& operand);
		bool checkNumberOperands(const Token& oper, const std::any& left, const std::any& right);
		ErrorHandler& errorHandler;

	};

}

#endif