#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class FileNameAlreadyTakenException :
		public FileSystemException
	{
	public:
		FileNameAlreadyTakenException(const std::string& filename);
	};

}

