#include "Parser.h"
#include "../Lox.h"

using namespace LoxCpp;
Parser::Parser(std::vector<Token> tokens, LoxException& loxException) : tokens(tokens), loxException(loxException) {}


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

std::unique_ptr<Expression> Parser::assignment()
{
	auto expression = this->equality();
	if (this->match({ TokenType::EQUAL }))
	{
		auto equalsToken = this->previous();
		auto expressionValue = this->assignment();

		if(auto* varExpression = dynamic_cast<VarExpression*>(expression.get()))
		{
			auto tokenName = varExpression->name;
			return std::make_unique<AssignExpression>(tokenName, std::move(expressionValue));
		}
		loxException.Add(std::string("Invalid assignment target"), 0);
		throw LoxException(loxException);
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
	return this->assignment();
}
std::unique_ptr<Statement> Parser::expressionStatement()
{
	auto expression = this->expression();
	std::string message("Expecting ; after expression");
	this->consume(TokenType::SEMICOLON, message);
	return std::make_unique<ExpressionStatement>(std::move(expression));
}
std::unique_ptr<Statement> Parser::statement()
{
	if (this->match({TokenType::PRINT}))
		return this->printStatement();
	return this->expressionStatement();
}
std::unique_ptr<Statement> Parser::printStatement()
{
	auto expression = this->expression();
	std::string message("Expecting ; after expression");
	this->consume(TokenType::SEMICOLON, message);
	return std::make_unique<Print>(std::move(expression));
}

std::unique_ptr<Statement> Parser::declaration()
{
	try
	{
		if (this->match({ TokenType::VAR }))
			return this->varDeclaration();
		return this->statement();
	}
	catch(std::runtime_error& error) // TODO: Implement runtime parse error
	{
		this->synchronize();
		return nullptr;
	}
}

std::unique_ptr<Statement> Parser::varDeclaration()
{
	std::string identifierMessage = "Expecting a variable name";
	std::string semicolonMessage = "Expecting ';' after variable declaration";
	Token tokenName = this->consume(TokenType::IDENTIFIER, identifierMessage);
	std::unique_ptr<Expression> expression = nullptr;
	if (this->match({ TokenType::EQUAL }))
		expression = this->expression();
	this->consume(TokenType::SEMICOLON, semicolonMessage);
	return std::make_unique<VarStatement>(tokenName, std::move(expression));
}

std::unique_ptr<Expression> Parser::unary() {
	std::vector types = { TokenType::BANG,TokenType::MINUS };
	if (this->match(types)) {
		Token op = this->previous();
		auto rightexpr = this->unary();
		auto expression = std::make_unique<UnaryExpression>(op, std::move(rightexpr));
		return expression;
	}
	return this->primary();
}


std::vector<std::unique_ptr<Statement>> Parser::Parse() {
	std::vector<std::unique_ptr<Statement>> statements;
	while(!this->isAtEnd())
	{
		statements.push_back(this->declaration());
	}
	return statements;
	
}

std::unique_ptr<Expression> Parser::primary()
{
	//TODO: Refactor this!

	std::vector falseType = { TokenType::FALSE };
	std::vector trueType = { TokenType::TRUE };
	std::vector nilType = { TokenType::NIL };

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

	if(this->match({TokenType::IDENTIFIER}))
	{
		return std::make_unique<VarExpression>(this->previous());
	}

	loxException.Add(std::string("Invalid expression"), this->peek().line);
	throw LoxException(loxException);
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


Token Parser::consume(TokenType type, std::string& message)
{
	if (this->check(type))
		return this->advance();

	//TODO Implement proper error handling
	this->loxException.Add(message, 0);
	throw LoxException(loxException);
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
	return this->peek().type == type;
}

Token Parser::previous() {
	return this->tokens.at(this->current - 1);
}
