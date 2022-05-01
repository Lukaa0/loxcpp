#pragma once
#ifndef LOX_H
#define LOX_H
#include <iostream>

namespace LoxCpp {
	static void RunFile(const std::string& path);

	static void RunPrompt();

	static bool Run(std::string source);

	void Error(int line, std::string message);

	static void Report(int line, std::string whereAt, std::string message);

}

#endif