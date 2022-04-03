
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <string>
#include <vector>
#include "ErrorModel.h"
namespace LoxCpp {
	class ErrorHandler {
	public:
		std::vector<ErrorModel> Errors;
		bool HasError;
		ErrorHandler();
		void Add(const std::string& message, int line);
	};
}
#endif

