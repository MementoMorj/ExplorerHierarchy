#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class WrongFileSizeFormatException :
		public FileSystemException
	{
	public:
		WrongFileSizeFormatException(std::string& sizeString);
	};

}

