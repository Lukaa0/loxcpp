#include "AstPrinter.h"
#include "../Utils/StringUtils.cpp"
using namespace LoxCpp;

void GenerateAST::defineAst(std::string& outputDir, std::string& baseName, std::vector<std::string>& types)
{
	std::string path = outputDir + "/" + baseName + ".cpp";
	std::ofstream writer{ path };
	writer << "#include \"vector\" \n"
		"class " + baseName + " {\n"
		"} \n";
	for(auto type : types){
		std::string className = trim(split(type,":")[0]);
		std::string fields = trim(split(type, ":")[1]);
		defineType(writer, baseName, className, fields);
	}
}

void GenerateAST::defineType(std::ofstream& writer, std::string& baseName, std::string& className, std::string& fieldList)
{
	writer << "class " + className + " : " + baseName + " {\n";
	//constr
	writer << "		" + className + "(" + fieldList + ") {\n";
	auto fields = split(fieldList, ", ");
	for (std::string field : fields) {
		auto name = split(field, " ")[1];
		writer << "		this->" + name + " = " + name + ";\n";
	}
	writer << "	}\n\n";

	//fields

	for (auto field : fields) {
		writer << "		const " + field + ";\n";
	}

	writer << "		}\n";
	writer.close();
}
