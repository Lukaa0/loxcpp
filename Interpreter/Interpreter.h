#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../Expressions/Expression.h"
#include "../Statements//Statement.h"
#include <iostream>
#include "../Models/LoxException.h"
#include "../Environment/Environment.h"
namespace LoxCpp{
	class Interpreter : ExpressionVisitor, StatementVisitor{
	public:
		Interpreter() {}
		std::any VisitBinary(BinaryExpression& expression) override;
		std::any VisitUnary(UnaryExpression& expression) override;
		std::any VisitLiteral(LiteralExpression& expression) override;
		std::any VisitGrouping(GroupingExpression& expression) override;
		std::any VisitAssignExpression(AssignExpression& expression) override;
		std::any VisitVarExpression(VarExpression& expression) override;
		std::any VisitExpressionStatement(ExpressionStatement& statement) override;
		std::any VisitPrint(Print& statement) override;
		std::any VisitBlock(Block& statement) override;
		std::any VisitClass(Class& statement) override;
		std::any VisitFunction(Function& statement) override;
		std::any VisitVarStatement(VarStatement& statement) override;

		void Interpret(std::vector<std::unique_ptr<Statement>> statements);
		std::string Output;
	private:
		std::string stringify(std::any object);
		bool checkNumberOperand(const Token& oper, const std::any& operand);
		bool checkNumberOperands(const Token& oper, const std::any& left, const std::any& right);
		void printOutput(std::any value);
		void executeBlock(std::vector<std::unique_ptr<Statement>> statements, Environment& env);
		LoxException loxException;
		Environment environment;

	};

}

#endif