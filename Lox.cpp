#include "Lox.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "vector"
#include "string"
#include "filesystem"
#include "Token/Token.h"
#include "Scanner/Scanner.h"
#include "Parser/Parser.h"

int main()
{
	std::cout << "Current working directory" << std::filesystem::current_path() << std::endl;
	std::string curdir(std::filesystem::current_path().string());
	//LoxCpp::RunFile(curdir + "\\test.txt");
	LoxCpp::Run("var testVar = #\"test string\";");
	system("PAUSE");
	return 0;
}
namespace LoxCpp {

	bool hadError = false;


	void RunFile(const std::string path) {
		std::ifstream stream(path);
		std::ostringstream  stringStream;
		stringStream << stream.rdbuf();
		stream.close();
		Run(stringStream.str());
	}

	void RunPrompt() {
		for (;;) {
			std::cout << "-> ";
			std::string line;
			std::getline(std::cin, line);
			if (line.size() == 0)
				break;
			Run(line);
		}
	}

	bool Run(std::string source) {
		Scanner scanner(source);
		std::vector<Token> tokens = scanner.ScanTokens();
		Parser parser = Parser(tokens);
		auto expression = parser.Parse();
		if (hadError)
			return hadError;
		return false;
	}

	void Error(int line, std::string message) {
		Report(line, "", message);
	}

	void Report(int line, std::string whereAt, std::string message) {

		std::cout << "[line " << line << "] Error " << whereAt << ": " << message;
		hadError = true;
	}
}