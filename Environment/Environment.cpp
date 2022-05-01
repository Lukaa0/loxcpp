
#include "Environment.h"
#include "../Token/Token.h"
#include "../Models/LoxException.h"
using namespace LoxCpp;

void Environment::Assign(Token name, std::any value)
{
	if (this->values.contains(name.lexeme))
	{
		this->values.insert({ name.lexeme, value });
	}

	if (this->enclosing != nullptr)
		enclosing->Assign(name, value);

	else
	{
		throw LoxException({ ErrorModel(std::string("Undefined variable " + name.lexeme), 0) });
	}
}

void Environment::Define(std::string name, std::any value)
{
	this->values.insert({ name,value });
}

std::any Environment::Get(Token name)
{
	if (this->values.contains(name.lexeme))
	{
		return this->values.find(name.lexeme)->second;
	}

	if (this->enclosing != nullptr)
		return enclosing->Get(name);

	throw LoxException({ ErrorModel(std::string("Undefined variable " + name.lexeme), 0) });
}
