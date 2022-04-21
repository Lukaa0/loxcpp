#include "base.h"
using namespace LoxCpp;
//TODO: More happy tests
TEST(LoxTests, ScanTokens) {
	std::string source = "var testStr = \"testStr\";";
	ErrorHandler errorHandler;
	Scanner scanner(source, errorHandler);
	Literal literal = "TEST";
	EXPECT_NO_THROW(scanner.ScanTokens());
	EXPECT_FALSE(errorHandler.HasError);
}


TEST(LoxTests, ValidateErrorMessageAtMissingQuote) {
	std::string source = "var testStr = \"testStr;";
	ErrorHandler errorHandler;
	Scanner scanner(source, errorHandler);
	auto tokens = scanner.ScanTokens();
	EXPECT_EQ(errorHandler.Errors.at(0).ErrorMessage, "Missing \" at the end of the string");
}

TEST(LoxTests, ValidateErrorMessageAtUnexpectedCharacter) {
	std::string source = "var str = $\"test\";";
	ErrorHandler errorHandler;
	Scanner scanner(source, errorHandler);
	auto tokens = scanner.ScanTokens();
	EXPECT_EQ(errorHandler.Errors.at(0).ErrorMessage, "Unexpected character");
	EXPECT_EQ(errorHandler.Errors.at(0).Line, 1);
}


