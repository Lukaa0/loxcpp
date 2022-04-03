#include "ErrorHandler.h"
using namespace LoxCpp;

ErrorHandler::ErrorHandler() : Errors()
{
	this->HasError = false;
}

void ErrorHandler::Add(const std::string& message, int line)
{
	this->Errors.push_back({message,line});
	this->HasError = true;
}

