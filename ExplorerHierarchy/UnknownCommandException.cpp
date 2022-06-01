#include "UnknownCommandException.h"

namespace FileSystem
{
	UnknownCommandException::UnknownCommandException(const std::string& commandName) :
		FileSystemException(std::string("unknown command named \"") + commandName + "\"")
	{

	}
}
