#ifndef ASTPRINTER_H
#define ASTPRINTER_H
#include "string"
#include <fstream>
#include "vector"

namespace LoxCpp{

	class GenerateAST{
	
	private:
		static void defineAst(std::string& outputDir, std::string& baseName, std::vector<std::string>& types);
		static void defineType(std::ofstream& writer, std::string& baseName, std::string& className, std::string& fieldList);
	};

}


#endif