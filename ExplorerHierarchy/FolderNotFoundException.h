#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class FolderNotFoundException :
		public FileSystemException
	{
	public:
		FolderNotFoundException(const std::string& foldername);
	};

}

