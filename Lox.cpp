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
#include <any>
#include <utility>
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
	Interpreter interpreter;
	void RunFile(const std::string& path) {
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
			if (line.empty())
				break;
			Run(line);
		}
	}

	bool Run(std::string source) {
		LoxException loxException{};
		try {
			Scanner scanner(std::move(source), loxException);
			const std::vector<Token> tokens = scanner.ScanTokens();
			Parser parser = Parser(tokens, loxException);
			auto statements = parser.Parse();

			interpreter.Interpret(std::move(statements));
		}
		catch(LoxException& err)
		{
			for(auto error : err.Errors)
			{
				Error(error.Line, error.ErrorMessage);
			}
		}
		if (hadError)
			return hadError;
		return true;
	}

	void Error(int line, std::string message) {
		Report(line, "", message);
	}

	void Report(const int line, const std::string whereAt, const std::string message) {

		std::cout << "[line " << line << "] Error " << whereAt << ": " << message;
		hadError = true;
	}

}