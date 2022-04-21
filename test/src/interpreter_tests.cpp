#include "base.h"
#include "../../Parser/Parser.h"
#include "../../Interpreter/Interpreter.h"
using namespace LoxCpp;

//TODO: Refactor 

std::unique_ptr<Expression> getExpression(std::string expressionSource, ErrorHandler errorHandler){
	Scanner scanner(expressionSource, errorHandler);
	auto tokens = scanner.ScanTokens();
	Parser parser(scanner.ScanTokens(), errorHandler);
	std::unique_ptr expression = parser.Parse();
	EXPECT_NO_THROW(parser.Parse());
	EXPECT_FALSE(errorHandler.HasError);
	return expression;
}
TEST(LoxTests, BinaryPlusFullNumberTest) {
	std::string expressionSource = "5 + 5";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("10"));
}

TEST(LoxTests, BinaryPlusFloatingNumberTest) {
	std::string expressionSource = "5.12 + 4.28";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("9.4"));
}

TEST(LoxTests, BinaryMinusFloatingNumberTest) {
	std::string expressionSource = "49.9 - 40.4";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_EQ(interpreter.Output, std::string("9.5"));
}

TEST(LoxTests, BinaryMinusFullNumberTest) {
	std::string expressionSource = "50 - 40";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("10"));
}

TEST(LoxTests, BinaryDivideFullNumberTest) {
	std::string expressionSource = "100 / 10";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("10"));
}

TEST(LoxTests, BinaryMultiplyFullNumberTest) {
	std::string expressionSource = "100 * 10";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("1000"));
}

TEST(LoxTests, BinaryGreaterNumberTest) {
	std::string expressionSource = "100 > 10";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("true"));
}

TEST(LoxTests, BinaryGreaterOrEqualNumberTest) {
	std::string expressionSource = "100 >= 100";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("true"));
}

TEST(LoxTests, BinaryLessOrEqualNumberTest) {
	std::string expressionSource = "10 <= 100";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("true"));
}

TEST(LoxTests, BinaryLessNumberTest) {
	std::string expressionSource = "10 < 100";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_FALSE(errorHandler.HasError);
	EXPECT_EQ(interpreter.Output, std::string("true"));
}

TEST(LoxTests, ShouldThrowOperandNumberPlusError) {
	std::string expressionSource = "10 + \"test\"";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_TRUE(errorHandler.HasError);
	EXPECT_EQ(errorHandler.Errors[0].ErrorMessage, std::string("Operand must either be numbers or strings"));
}

TEST(LoxTests, ShouldThrowInvalidExpressionTest) {
	std::string expressionSource = "2===2";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_TRUE(errorHandler.HasError);
	EXPECT_EQ(errorHandler.Errors[0].ErrorMessage, std::string("Invalid Expression"));
}
TEST(LoxTests, ShouldThrowOperandMustBeNumberTest) {
	std::string expressionSource = "2 - \"test\"";
	ErrorHandler errorHandler;
	std::unique_ptr<Expression> expression = getExpression(expressionSource, errorHandler);

	Interpreter interpreter(errorHandler);
	interpreter.Interpret(std::move(expression));
	EXPECT_TRUE(errorHandler.HasError);
	EXPECT_EQ(errorHandler.Errors[0].ErrorMessage, std::string("Operand must be a number"));
}
