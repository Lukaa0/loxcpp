#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <string_view>

namespace LoxCpp
{

	enum class TokenType{
	  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	  BANG, BANG_EQUAL,
	  EQUAL, EQUAL_EQUAL,
	  GREATER, GREATER_EQUAL,
	  LESS, LESS_EQUAL,

	  IDENTIFIER, STRING, NUMBER,

	  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
	  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	  END
	
	};

	class Token{
	//TODO : Use std::variant for literals
	public:
		std::string lexeme;
		std::string literal;
		TokenType type;
		int line;
		Token(TokenType type, std::string lexeme, std::string literal, int line);
		std::string ToString();
	};
}
#endif