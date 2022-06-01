#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class UnknownFileTypeException :
		public FileSystemException
	{
	public:
		UnknownFileTypeException(const std::string& type);
	};

}

