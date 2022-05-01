
#ifndef LOX_EXCEPTION_H
#define LOX_EXCEPTION_H
#include <string>
#include <vector>
#include "ErrorModel.h"
namespace LoxCpp {
	class LoxException : public std::exception {
	public:
		std::vector<ErrorModel> Errors;
		bool HasError();
		LoxException() = default;
		LoxException(std::vector<ErrorModel> errors) : Errors(std::move(errors)) {}
		void Add(const std::string& message, int line);
	};
}
#endif

