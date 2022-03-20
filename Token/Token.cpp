#include "Token.h"
#include "string"
using namespace LoxCpp;


Token::Token(TokenType type, std::string lexeme, std::string literal, int line)
{
	this->type = type;
	this->lexeme = lexeme;
	this->literal = literal;
	this->line = line;
}

std::string Token::ToString() {
	//TODO: Token enum to string
	return ("token " + lexeme + " " + literal);
}