#ifndef STATEMENT_H
#define STATEMENT_H
#include <memory>
#include "../Token/Token.h"
#include <any>
#include <vector>
#include "../Expressions/Expression.h"

namespace LoxCpp {
	class StatementVisitor;
	class Block;
	class Class;
	class ExpressionStatement;
	class Function;
	class Print;
	class VarStatement;
	class Statement {
	public:
		virtual ~Statement() = default;
		virtual std::any Accept(StatementVisitor& statementVisitor) = 0;
	};

	class StatementVisitor {
	public:
		virtual ~StatementVisitor() = default;
		virtual std::any VisitBlock(Block& statement) = 0;
		virtual std::any VisitClass(Class& statement) = 0;
		virtual std::any VisitExpressionStatement(ExpressionStatement& statement) = 0;
		virtual std::any VisitFunction(Function& statement) = 0;
		virtual std::any VisitPrint(Print& statement) = 0;
		virtual std::any VisitVarStatement(VarStatement& statement) = 0;
	};


	class Block : public Statement {
	public:
		Block(std::vector<std::unique_ptr<Statement>> statements);
		std::any Accept(StatementVisitor& statementVisitor) override { return statementVisitor.VisitBlock(*this); }
		std::vector<std::unique_ptr<Statement>> statements;
	};

	class Class : public Statement {
	public:
		Class(Token name, std::unique_ptr<Expression> super, std::vector<std::unique_ptr<Function>> methods);
		std::any Accept(StatementVisitor& statementVisitor) override { return statementVisitor.VisitClass(*this); }
		std::vector<std::unique_ptr<Statement>> statements;
		Token name;
		std::unique_ptr<Expression> super;
		std::vector<std::unique_ptr<Function>> methods;

	};

	class ExpressionStatement : public Statement {
	public:
		ExpressionStatement(std::unique_ptr<Expression> expression);
		std::any Accept(StatementVisitor& statementVisitor) override { return statementVisitor.VisitExpressionStatement(*this); }
		std::unique_ptr<Expression> expression;

	};

	class Function : public Statement {
	public:
		Function(Token name, std::vector<Token> parameters, std::unique_ptr<Block> statements);
		std::any Accept(StatementVisitor& statementVisitor) override { return statementVisitor.VisitFunction(*this); }
		Token name;
		std::vector<Token> parameters;
		std::unique_ptr<Block> statement;

	};

	class Print : public Statement {
	public:
		Print(std::unique_ptr<Expression> expression);
		std::any Accept(StatementVisitor& statementVisitor) override { return statementVisitor.VisitPrint(*this); }
		std::unique_ptr<Expression> expression;

	};

	class VarStatement : public Statement {
	public:
		VarStatement(Token name, std::unique_ptr<Expression> initializer);
		std::any Accept(StatementVisitor& statementVisitor) override { return statementVisitor.VisitVarStatement(*this); }
		std::unique_ptr<Expression> expression;
		Token name;
	};


}

#endif