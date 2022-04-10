#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include "string"
#include "vector"
namespace Utils {
	std::vector<std::string> split(std::string& input, std::string delimiter);
	std::string trim(std::string& input);
}
#endif