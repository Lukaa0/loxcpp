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
#include <gtest/gtest.h>
#include "test/src/parser_tests.cpp"
#include "test/src/scanner_tests.cpp"
#include "Interpreter/Interpreter.h"
int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc,argv);
	std::cout << "Current working directory" << std::filesystem::current_path() << std::endl;
	std::string curdir(std::filesystem::current_path().string());
	//LoxCpp::RunFile(curdir + "\\test.txt");
	LoxCpp::RunPrompt();
	return RUN_ALL_TESTS();
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
			std::cout << std::endl;
			std::cout << "-> ";
			std::string line;
			std::getline(std::cin, line);
			if (line.size() == 0)
				break;
			Run(line);
		}
	}

	bool Run(std::string source) {
		ErrorHandler errorHandler;
		Scanner scanner(source, errorHandler);
		std::vector<Token> tokens = scanner.ScanTokens();
		Parser parser = Parser(tokens, errorHandler);
		auto expression = parser.Parse();

		Interpreter interpreter(errorHandler);
		interpreter.Interpret(std::move(expression));
		if (hadError)
			return hadError;
		return true;
	}

	void Error(int line, std::string message) {
		Report(line, "", message);
	}

	void Report(int line, std::string whereAt, std::string message) {

		std::cout << "[line " << line << "] Error " << whereAt << ": " << message;
		hadError = true;
	}
}