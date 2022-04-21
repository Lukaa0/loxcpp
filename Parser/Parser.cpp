#include "Parser.h"
#include "../Lox.h"

using namespace LoxCpp;
Parser::Parser(std::vector<Token> tokens, ErrorHandler& errorHandler) : tokens(tokens), errorHandler(errorHandler) {}


std::unique_ptr<Expression> Parser::equality()
{
	auto expression = comparison();
	std::vector<TokenType> types = { TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL };
	while (this->match(types)) {
		Token op = this->previous();
		auto rightexpr = this->comparison();
		expression = std::make_unique<BinaryExpression>(std::move(expression), op, std::move(rightexpr));
	}
	return expression;
}

std::unique_ptr<Expression> Parser::comparison() {
	std::unique_ptr<Expression> expression = this->term();
	std::vector<TokenType> types = { TokenType::GREATER,TokenType::GREATER_EQUAL,TokenType::LESS,TokenType::LESS_EQUAL };
	while (this->match(types)) {
		Token op = this->previous();
		auto rightexpr = this->term();
		expression = std::make_unique<BinaryExpression>(std::move(expression), op, std::move(rightexpr));
	}
	return expression;
}

std::unique_ptr<Expression> Parser::term() {
	std::unique_ptr<Expression> expression = this->factor();
	std::vector<TokenType> types = { TokenType::MINUS,TokenType::PLUS };
	while (this->match(types)) {
		Token op = this->previous();
		auto rightexpr = this->factor();
		expression = std::make_unique<BinaryExpression>(std::move(expression), op, std::move(rightexpr));
	}
	return expression;
}

std::unique_ptr<Expression> Parser::factor() {
	std::unique_ptr<Expression> expression = this->unary();
	std::vector<TokenType> types = { TokenType::SLASH,TokenType::STAR };
	while (this->match(types)) {
		Token op = this->previous();
		auto rightexpr = this->unary();
		expression = std::make_unique<BinaryExpression>(std::move(expression), op, std::move(rightexpr));
	}
	return expression;
}

std::unique_ptr<Expression> Parser::expression() {
	return this->equality();
}
std::unique_ptr<Expression> Parser::unary() {
	std::vector<TokenType> types = { TokenType::BANG,TokenType::MINUS };
	if (this->match(types)) {
		Token op = this->previous();
		auto rightexpr = this->unary();
		auto expression = std::make_unique<UnaryExpression>(op, std::move(rightexpr));
		return expression;
	}
	return this->primary();
}
std::unique_ptr<Expression> Parser::Parse() {
	return this->expression();
}

std::unique_ptr<Expression> Parser::primary()
{
	//TODO: Refactor this!

	std::vector<TokenType> falseType = { TokenType::FALSE };
	std::vector<TokenType> trueType = { TokenType::TRUE };
	std::vector<TokenType> nilType = { TokenType::NIL };

	if (this->match(falseType))
		return std::make_unique<LiteralExpression>(false);
	if (this->match(trueType))
		return std::make_unique<LiteralExpression>(true);
	if (this->match(nilType))
		return std::make_unique<LiteralExpression>(nullptr);

	if (this->match({ TokenType::NUMBER, TokenType::STRING }))
		return std::make_unique<LiteralExpression>(this->previous().literal);

	if (this->match({ TokenType::LEFT_PAREN })) {
		std::string message = "expected \')\' after expression";
		this->consume(TokenType::RIGHT_PAREN, message);
		return std::make_unique<GroupingExpression>(this->expression());
	}

	return std::make_unique<LiteralExpression>(true);

}


bool Parser::match(std::vector<TokenType> types) {
	for (TokenType type : types) {
		if (this->check(type)) {
			this->advance();
			return true;
		}
	}
	return false;
}

Token Parser::advance() {
	if (!this->isAtEnd())
		this->current++;
	return this->previous();
}

void Parser::synchronize() {
	this->advance();

	while (!this->isAtEnd()) {
		if (this->previous().type == TokenType::SEMICOLON)
			return;
		switch (this->peek().type) {
		case TokenType::CLASS:
		case TokenType::FUN:
		case TokenType::VAR:
		case TokenType::FOR:
		case TokenType::IF:
		case TokenType::WHILE:
		case TokenType::PRINT:
		case TokenType::RETURN:
			return;
		}
		this->advance();
	}

}


std::optional<Token> Parser::consume(TokenType type, std::string& message)
{
	if (this->check(type))
		return this->advance();

	//TODO Implement proper error handling
	this->errorHandler.Add(message, 0);
	Error(0, message);
	return std::nullopt;
}

bool Parser::isAtEnd() {
	return this->peek().type == TokenType::END;
}

Token Parser::peek() {
	return this->tokens.at(this->current);
}

bool Parser::check(TokenType type)
{
	if (this->isAtEnd())
		return false;
	auto sr = this->peek();
	return this->peek().type == type;
}

Token Parser::previous() {
	return this->tokens.at(this->current - 1);
}
