#ifndef ERROR_H
#define ERROR_H
#include <string>
#include <vector>
namespace LoxCpp {
	class ErrorModel {
	public:
		std::string ErrorMessage;
		int Line;
		ErrorModel(const std::string& errorMessage, int line);
	};

}
#endif