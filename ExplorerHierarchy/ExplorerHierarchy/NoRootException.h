#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class NoRootException :
		public FileSystemException
	{
	public:
		NoRootException();
	};
}


