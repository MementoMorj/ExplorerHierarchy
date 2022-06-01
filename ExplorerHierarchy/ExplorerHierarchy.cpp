#define _CRT_SECURE_NO_WARNINGS

#include "CommandAnalyzer.h"
#include <iostream>
#include <Windows.h>

int main()
{
	using namespace FileSystem;

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	CommandAnalyzer commandAnalyzer(std::cin);
	commandAnalyzer.analyze();
	return 0;
}

