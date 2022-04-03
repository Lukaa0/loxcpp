#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>
#include "../Token/Token.h"

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
		virtual void Accept(ExpressionVisitor& expressionVisitor) = 0;
	};

	class ExpressionVisitor {
	public:
		virtual void VisitBinary(BinaryExpression& expression) = 0;
		virtual void VisitUnary(UnaryExpression& expression) = 0;
		virtual void VisitLiteral(LiteralExpression& expression) = 0;
		virtual void VisitGrouping(GroupingExpression& expression) = 0;
	};


	class BinaryExpression : public Expression {
	public:
		BinaryExpression(std::unique_ptr<Expression> left, Token& op, std::unique_ptr<Expression> right);
		void Accept(ExpressionVisitor& expressionVisitor) override { expressionVisitor.VisitBinary(*this); }
	private:
		std::unique_ptr<Expression> left;
		std::unique_ptr<Expression> right;
		Token op;
	};

	class UnaryExpression : public Expression {

	public:
		UnaryExpression(Token& op, std::unique_ptr<Expression> right);
		void Accept(ExpressionVisitor& expressionVisitor) override { expressionVisitor.VisitUnary(*this); }
	private:
		std::unique_ptr<Expression> right;
		Token op;
	};
	class LiteralExpression : public Expression{
	
	public:
		Literal literal;
		LiteralExpression(Literal literal);
		void Accept(ExpressionVisitor& expressionVisitor) override { expressionVisitor.VisitLiteral(*this); }
	};

	class GroupingExpression : public Expression{
	
	public:
		std::unique_ptr<Expression> expression;
		GroupingExpression(std::unique_ptr<Expression> expression);
		void Accept(ExpressionVisitor& expressionVisitor) override { expressionVisitor.VisitGrouping(*this); }
	};
}

#endif