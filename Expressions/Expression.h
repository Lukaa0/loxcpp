#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>
#include "../Token/Token.h"
#include <any>
#include <memory>

namespace LoxCpp {

	class ExpressionVisitor;
	class BinaryExpression;
	class UnaryExpression;
	class LiteralExpression;
	class GroupingExpression;
	class Expression;

	class Expression {
	public:
		virtual ~Expression() = default;
		virtual std::any Accept(ExpressionVisitor& expressionVisitor) = 0;
	};

	class ExpressionVisitor {
	public:
		virtual std::any VisitBinary(BinaryExpression& expression) = 0;
		virtual std::any VisitUnary(UnaryExpression& expression) = 0;
		virtual std::any VisitLiteral(LiteralExpression& expression) = 0;
		virtual std::any VisitGrouping(GroupingExpression& expression) = 0;
	};


	class BinaryExpression : public Expression {
	public:
		BinaryExpression(std::unique_ptr<Expression> left, Token& op, std::unique_ptr<Expression> right);
		std::any Accept(ExpressionVisitor& expressionVisitor) override { return expressionVisitor.VisitBinary(*this); }
		std::unique_ptr<Expression> left;
		std::unique_ptr<Expression> right;
		Token op;
	};

	class UnaryExpression : public Expression {

	public:
		UnaryExpression(Token& op, std::unique_ptr<Expression> right);
		std::any Accept(ExpressionVisitor& expressionVisitor) override { return expressionVisitor.VisitUnary(*this); }
		std::unique_ptr<Expression> right;
		Token op;
	};
	class LiteralExpression : public Expression{
	
	public:
		Literal literal;
		LiteralExpression(Literal literal);
		std::any Accept(ExpressionVisitor& expressionVisitor) override { return expressionVisitor.VisitLiteral(*this); }
	};

	class GroupingExpression : public Expression{
	
	public:
		const std::unique_ptr<Expression> expression;
		GroupingExpression(std::unique_ptr<Expression> expression);
		std::any Accept(ExpressionVisitor& expressionVisitor) override { return expressionVisitor.VisitGrouping(*this); }
	};
}

#endif