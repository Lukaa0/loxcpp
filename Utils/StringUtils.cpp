#include "string"
#include "vector"
namespace LoxCpp {
	std::vector<std::string> split(std::string& input, std::string delimiter) {
		std::string word;
		size_t end;
		size_t start = 0;
		std::vector<std::string> result;
		while (end = input.find(delimiter,start) != std::string::npos)
		{
			word = input.substr(start, end - start);
			start = end + delimiter.length();
			result.push_back(word);
		}
		result.push_back(input.substr(start));
		return result;
	}

	std::string trim(std::string& input){
		const std::string WHITESPACE = " \n\r\t\f\v";
		size_t start = input.find_first_not_of(WHITESPACE);
		std::string ltrimmed = (start == std::string::npos) ? "" : input.substr(start);
		size_t end = ltrimmed.find_last_not_of(WHITESPACE);
		return (end == std::string::npos) ? "" : ltrimmed.substr(0, end + 1);	}
}