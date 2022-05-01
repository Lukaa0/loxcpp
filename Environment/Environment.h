#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <map>
#include <any>
#include "string"
#include "../Token/Token.h"
namespace LoxCpp
{
	class Environment
	{
	public:
		std::map<std::string, std::any> values;
		void Assign(Token name, std::any value);
		void Define(std::string name, std::any value);

		std::any Get(Token name);

		Environment* enclosing;

		Environment(Environment* enclosing) : enclosing(enclosing) {}
		Environment() : enclosing(nullptr) {}
	};
}


#endif