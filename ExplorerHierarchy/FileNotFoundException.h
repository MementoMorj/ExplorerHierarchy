#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class FileNotFoundException :
		public FileSystemException
	{
	public:
		FileNotFoundException(const std::string& filename);
	};
}


