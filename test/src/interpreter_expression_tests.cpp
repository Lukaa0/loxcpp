#include "base.h"
#include "../../Parser/Parser.h"
#include "../../Interpreter/Interpreter.h"
using namespace LoxCpp;

//TODO: Refactor 

std::vector<std::unique_ptr<Statement>> getStatements(std::string source, LoxException errorHandler) {
	Scanner scanner(source, errorHandler);
	auto tokens = scanner.ScanTokens();
	Parser parser(scanner.ScanTokens(), errorHandler);
	auto statement = parser.Parse();
	return statement;
}
TEST(LoxTests, BinaryPlusFullNumberTest) {
	std::string source = "5 + 5;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("10"));
}

TEST(LoxTests, BinaryPlusFloatingNumberTest) {
	std::string source = "5.12 + 4.28;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("9.4"));
}

TEST(LoxTests, BinaryMinusFloatingNumberTest) {
	std::string source = "49.9 - 40.4;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_EQ(interpreter.Output, std::string("9.5"));
}

TEST(LoxTests, BinaryMinusFullNumberTest) {
	std::string source = "50 - 40;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("10"));
}

TEST(LoxTests, BinaryDivideFullNumberTest) {
	std::string source = "100 / 10;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("10"));
}

TEST(LoxTests, BinaryMultiplyFullNumberTest) {
	std::string source = "100 * 10;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("1000"));
}

TEST(LoxTests, BinaryGreaterNumberTest) {
	std::string source = "100 > 10;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("true"));
}

TEST(LoxTests, BinaryGreaterOrEqualNumberTest) {
	std::string source = "100 >= 100;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("true"));
}

TEST(LoxTests, BinaryLessOrEqualNumberTest) {
	std::string source = "10 <= 100;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("true"));
}

TEST(LoxTests, BinaryLessNumberTest) {
	std::string source = "10 < 100;";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	interpreter.Interpret(std::move(statements));
	EXPECT_FALSE(errorHandler.HasError());
	EXPECT_EQ(interpreter.Output, std::string("true"));
}

TEST(LoxTests, ShouldThrowOperandNumberPlusError) {
	std::string source = "10 + \"test\"";
	LoxException errorHandler;
	EXPECT_THROW(getStatements(source, errorHandler), LoxException);
}

TEST(LoxTests, ShouldThrowInvalidExpressionTest) {
	std::string source = "2===2;";
	LoxException errorHandler;
	Scanner scanner(source, errorHandler);
	auto tokens = scanner.ScanTokens();
	Parser parser(scanner.ScanTokens(), errorHandler);
	EXPECT_THROW(parser.Parse(), LoxException);
	EXPECT_TRUE(errorHandler.HasError());
	EXPECT_EQ(errorHandler.Errors[0].ErrorMessage, std::string("Invalid expression"));
}
TEST(LoxTests, ShouldThrowOperandMustBeNumberTest) {
	std::string source = "2 - \"test\";";
	LoxException errorHandler;
	auto statements = getStatements(source, errorHandler);

	Interpreter interpreter;
	try
	{
		interpreter.Interpret(std::move(statements));
	}
	catch (LoxException& exception) {
		EXPECT_EQ(exception.Errors[0].ErrorMessage, std::string("Operand must be a number"));
	}
}
