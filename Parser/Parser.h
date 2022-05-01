#include <vector>
#include "../Token/Token.h"
#include "../Expressions/Expression.h"
#include <memory>
#include "../Models/LoxException.h"
#include <optional>
#include "../Statements/Statement.h"

namespace LoxCpp {

	class Parser {
	private:
		std::vector<Token> tokens;
		int current = 0;
		LoxException& loxException;
		std::unique_ptr<Expression> equality();
		std::unique_ptr<Expression> assignment();
		std::unique_ptr<Expression> comparison();
		std::unique_ptr<Expression> term();
		std::unique_ptr<Expression> factor();
		std::unique_ptr<Expression> unary();
		std::unique_ptr<Expression> primary();
		std::unique_ptr<Expression> expression();
		std::unique_ptr<Statement> expressionStatement();
		std::unique_ptr<Statement> statement();
		std::unique_ptr<Statement> printStatement();
		std::unique_ptr<Statement> declaration();
		std::unique_ptr<Statement> varDeclaration();

		bool match(std::vector<TokenType> types);
		Token consume(TokenType type, std::string& message);
		Token advance();
		bool isAtEnd();
		bool check(TokenType type);
		Token peek();
		void synchronize();
		Token previous();


	public:
		std::vector<std::unique_ptr<Statement>> Parse();
		Parser(std::vector<Token> tokens, LoxException& loxException);
	};

}