#ifndef ASTGENERATOR_H
#define ASTGENERATOR_H
#include "string"
#include <fstream>
#include "vector"

namespace LoxCpp{

	class GenerateAST{
	
	public:
		static void DefineAst(std::string& outputDir, std::string& baseName, std::vector<std::string>& types);
		static void DefineType(std::ofstream& writer, const std::string& baseName, const std::string& className, std::string& fieldList);
	};

}


#endif