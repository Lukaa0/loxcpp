#ifndef SCANNER_H
#define SCANNER_H
#include <vector>
#include "../Token/Token.h"
#include <map>
#include <variant>
#include "../Models/ErrorHandler.h"
namespace LoxCpp{

	class Scanner{
	public:
		std::string source;
		std::vector<Token> tokens;
		Scanner(std::string source, ErrorHandler& errorHandler);
		std::vector<Token> ScanTokens();
	private:
		int start = 0;
		int current = 0;
		int line = 1;
		ErrorHandler& errorHandler;
		std::map<std::string, TokenType> keywords;

		//helper functions
		bool isAtEnd();
		void scanToken();
		char advance();
		void addToken(TokenType type);
		void addToken(TokenType type, Literal literal);
		bool match(char expected);
		char peek();
		void handleString();
		bool isDigit(char c);
		void number();
		char peekNext();
		bool isAlpha(char c);
		bool isAlphaNumeric(char c);
		void id();


	};
}
#endif