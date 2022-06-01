#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class FinalFullPathTooLongException :
		public FileSystemException
	{
	public:
		FinalFullPathTooLongException(const File* file, const std::string& filename);
	};

}
