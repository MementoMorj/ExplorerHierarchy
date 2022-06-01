#include "NoRootException.h"

namespace FileSystem
{
	FileSystem::NoRootException::NoRootException() :
		FileSystemException("current folder has no root folder")
	{
	}
}

