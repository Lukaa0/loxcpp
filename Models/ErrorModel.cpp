#include "ErrorModel.h"
using namespace LoxCpp;

ErrorModel::ErrorModel(const std::string& errorMessage, int line)
{
	this->ErrorMessage = errorMessage;
	this->Line = line;
}