#include "FileNotFoundException.h"

namespace FileSystem
{
	FileNotFoundException::FileNotFoundException(const std::string& filename) :
		FileSystemException(std::string("file with name \"") + filename + "\" not found")
	{
	}

}
