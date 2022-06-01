#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class UnknownCommandException :
		public FileSystemException
	{
	public:
		UnknownCommandException(const std::string& commandName);
	};
}

