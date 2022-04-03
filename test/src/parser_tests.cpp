#include "base.h"
using namespace LoxCpp;

TEST(LoxTests, ParserNoException) {
	std::string source = "var testStr = \"testStr\";";
	ErrorHandler errorHandler;
	Scanner scanner(source, errorHandler);
	Parser parser(scanner.ScanTokens(), errorHandler);
	EXPECT_NO_THROW(parser.Parse());
}

TEST(LoxTests, ExpectedRightParanthesis) {

	std::string expressionSource = "(a == b";
	ErrorHandler errorHandler;
	Scanner scanner(expressionSource, errorHandler);
	auto tokens = scanner.ScanTokens();
	Parser parser(scanner.ScanTokens(), errorHandler);
	parser.Parse();
	EXPECT_TRUE(errorHandler.HasError);
	EXPECT_EQ(errorHandler.Errors.at(0).ErrorMessage, "expected \')\' after expression");

}

