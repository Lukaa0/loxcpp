#include "base.h"
#include "vector"
#include "filesystem"
#include "../../AST/AstGenerator.h"
#include "../../Utils/StringUtils.h"
using namespace LoxCpp;

TEST(LoxTests, AstGenerates) {
	auto currentDir = std::filesystem::current_path().string();
	std::vector<std::string> types({ "Binary : Expression left, Token operator, Expression right" });
	GenerateAST::DefineAst(currentDir, std::string("TestBaseClass"), types);
	std::ifstream file(currentDir + "/TestBaseClass.cpp");
	EXPECT_TRUE(file.is_open());
	std::string fileContent(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));

	EXPECT_TRUE(fileContent.find("class TestBaseClass {") != std::string::npos);
	EXPECT_TRUE(fileContent.find("Binary(Expression left, Token operator, Expression right) {") != std::string::npos);
	EXPECT_TRUE(fileContent.find("class Binary : TestBaseClass {") != std::string::npos);

}