#include "AstGenerator.h"
#include "../Utils/StringUtils.h"
using namespace LoxCpp;

void GenerateAST::DefineAst(std::string& outputDir, std::string& baseName, std::vector<std::string>& types)
{
	std::string path = outputDir + "/" + baseName + ".cpp";
	std::ofstream writer{ path };
	writer << "#include \"vector\" \n"
		"class " + baseName + " {\n"
		"} \n";
	for(auto type : types){
		std::string className = Utils::trim(Utils::split(type,":")[0]);
		std::string fields = Utils::trim(Utils::split(type, ":")[1]);
		DefineType(writer, baseName, className, fields);
	}
}

void GenerateAST::DefineType(std::ofstream& writer, std::string& baseName, std::string& className, std::string& fieldList)
{
	writer << "class " + className + " : " + baseName + " {\n";
	//constr
	writer << "		" + className + "(" + fieldList + ") {\n";
	auto fields = Utils::split(fieldList, ", ");
	for (std::string field : fields) {
		auto name = Utils::split(field, " ")[1];
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
