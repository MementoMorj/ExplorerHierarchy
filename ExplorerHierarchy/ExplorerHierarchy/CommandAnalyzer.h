#pragma once
#include "FileSystem.h"
#include <iostream>

namespace FileSystem
{
	class CommandAnalyzer
	{
	private:
		Folder mainFolder{ "" };
		Folder* currentFolder = &mainFolder;
		std::istream* in;

	public:
		CommandAnalyzer(std::istream& in);

		void analyze();
	};
}


