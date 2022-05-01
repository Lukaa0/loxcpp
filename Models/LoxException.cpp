#include "LoxException.h"
using namespace LoxCpp;
void LoxException::Add(const std::string& message, int line)
{
	this->Errors.push_back({message,line});
}

bool LoxException::HasError()
{
	if (this->Errors.empty())
		return false;
	return true;
}

