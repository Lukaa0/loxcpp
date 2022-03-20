#include "Scanner.h"
#include "string"
#include "../Lox.h"

using namespace LoxCpp;

Scanner::Scanner(std::string source) {
	this->source = source;
	this->keywords = {
		{"and",     TokenType::AND},
		{"class",   TokenType::CLASS},
		{"else",    TokenType::ELSE},
		{"false",   TokenType::FALSE},
		{"for",     TokenType::FOR},
		{"fun",     TokenType::FUN},
		{"if",      TokenType::IF},
		{"nil",     TokenType::NIL},
		{"or",      TokenType::OR},
		{"print",   TokenType::PRINT},
		{"return",  TokenType::RETURN},
		{"super",   TokenType::SUPER},
		{"this",    TokenType::THIS},
		{"true",    TokenType::TRUE},
		{"var",     TokenType::VAR},
		{"while",   TokenType::WHILE},
	};
}

std::vector<Token> Scanner::ScanTokens()
{
	while (!isAtEnd()) {
		this->start = this->current;
		this->scanToken();
	}
	this->tokens.push_back(Token(TokenType::END, "", "", this->line));
	return this->tokens;
}

bool Scanner::isAtEnd()
{
	return this->current >= this->source.length();
}

//TODO: Add multi comment feature
void Scanner::scanToken()
{
	char c = advance();
	switch (c)
	{
	case '(': this->addToken(TokenType::LEFT_PAREN); break;
	case ')': this->addToken(TokenType::RIGHT_PAREN); break;
	case '{': this->addToken(TokenType::LEFT_BRACE); break;
	case '}': this->addToken(TokenType::RIGHT_BRACE); break;
	case ',': this->addToken(TokenType::COMMA); break;
	case '.': this->addToken(TokenType::DOT); break;
	case '-': this->addToken(TokenType::MINUS); break;
	case '+': this->addToken(TokenType::PLUS); break;
	case ';': this->addToken(TokenType::SEMICOLON); break;
	case '*': this->addToken(TokenType::STAR); break;
	case '!':
		this->addToken(this->match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
		break;
	case '=':
		this->addToken(this->match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
		break;
	case '<':
		this->addToken(this->match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
		break;
	case '>':
		this->addToken(this->match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
		break;

	case '/':
		if (this->match('/')) {
			while (this->peek() != '\n' && !this->isAtEnd())
				this->advance();
		}
		else {
			this->addToken(TokenType::SLASH);
		}
		break;
	case ' ':
	case '\r':
	case '\t':
		break;

	case '\n':
		this->line++;
		break;

	case '"': this->handleString(); break;
	case 'o':
		if (this->match('r')) {
			this->addToken(TokenType::OR);
		}
		break;

	default: {
		if (this->isDigit(c))
			this->number();
		else if (this->isAlpha(c))
			this->id();
		else
			Error(this->line, "Unexpected character");
		this->ErrorMessage = "Unexpected character at " + std::to_string(this->line);
	}
	}
}

char Scanner::advance()
{
	return this->source.at(this->current++);
}

void Scanner::addToken(TokenType type)
{
	addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal)
{
	std::string lexeme = this->source.substr(this->start, this->current);
	this->tokens.push_back(Token(type, lexeme, literal, this->line));
}

bool Scanner::match(char expected)
{
	if (!this->isAtEnd() || this->source.at(current) != expected) {
		current++;
		return true;
	}
	return false;
}

char Scanner::peek()
{
	if (!this->isAtEnd()) {
		return this->source.at(current);
	}
	return '\0';
}

void Scanner::handleString()
{
	while (this->peek() != '"' && !this->isAtEnd()) {
		this->advance();
	}

	if (this->isAtEnd()) {
		Error(this->line, "Missing \" at the end of the string");
		this->ErrorMessage = "Missing \" at the end of the string";
		return;
	}

	this->advance();

	std::string val = source.substr(this->start + 1, this->current - this->start - 2);
	addToken(TokenType::STRING, val);
}


void Scanner::number()
{
	while (this->isDigit(this->peek()))
		this->advance();
	if (this->peek() == '.' && this->isDigit(this->peekNext()))
	{
		// continue looping after the floating point
		this->advance();
		while (this->isDigit(this->peek()))
			this->advance();
	}
	// TODO: after replacing string with std::variant, do this ; std::stof(this->source.substr(this->start, this->current))
	this->addToken(TokenType::NUMBER, this->source.substr(this->start, this->current));

}

char Scanner::peekNext()
{
	if (this->current + 1 < this->source.length())
		return this->source.at(this->current + 1);
	return '\0';
}

bool Scanner::isAlpha(char c)
{
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		c == '_';
}

bool Scanner::isAlphaNumeric(char c)
{
	return this->isAlpha(c) || this->isDigit(c);
}

void Scanner::id()
{
	while (this->isAlphaNumeric(this->peek()))
		this->advance();

	std::string key = this->source.substr(this->start, this->current);
	TokenType type = TokenType::IDENTIFIER;
	auto search = this->keywords.find(key);
	if (search != this->keywords.end()) {
		type = search->second;
	}

	this->addToken(type);
}

bool Scanner::isDigit(char c) {
	return c >= '0' && c <= '9';
}
