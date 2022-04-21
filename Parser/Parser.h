#include <vector>
#include "../Token/Token.h"
#include "../Expressions/Expression.h"
#include <memory>
#include "../Models/ErrorHandler.h"
#include <optional>

namespace LoxCpp {

	class Parser {
	private:
		std::vector<Token> tokens;
		int current = 0;
		ErrorHandler& errorHandler;
		std::unique_ptr<Expression> equality();
		std::unique_ptr<Expression> comparison();
		std::unique_ptr<Expression> term();
		std::unique_ptr<Expression> factor();
		std::unique_ptr<Expression> unary();
		std::unique_ptr<Expression> primary();
		std::unique_ptr<Expression> expression();

		bool match(std::vector<TokenType> types);
		std::optional<Token> consume(TokenType type, std::string& message);
		Token advance();
		bool isAtEnd();
		bool check(TokenType type);
		Token peek();
		void synchronize();
		Token previous();


	public:
		std::unique_ptr<Expression> Parse();
		Parser(std::vector<Token> tokens, ErrorHandler& errorHandler);
	};

}