#include "Token.h"
#include "string"
using namespace LoxCpp;


Token::Token(TokenType type, std::string lexeme, Literal literal, int line)
{
	this->type = type;
	this->lexeme = lexeme;
	this->literal = literal;
	this->line = line;
}

std::string Token::ToString() {
	//TODO: Token enum to string
	std::string strLiteral = "";

	if (literal.type() == typeid(std::string)) {
		strLiteral = std::any_cast<std::string>(literal);
	}
	return ("token " + lexeme + " " + strLiteral);
}