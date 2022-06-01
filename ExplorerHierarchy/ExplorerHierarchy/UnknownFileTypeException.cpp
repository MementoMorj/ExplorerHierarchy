#include "UnknownFileTypeException.h"

namespace FileSystem
{
	UnknownFileTypeException::UnknownFileTypeException(const std::string& type) :
		FileSystemException(std::string("unknown type named \"") + type + "\"")
	{
	}
}

