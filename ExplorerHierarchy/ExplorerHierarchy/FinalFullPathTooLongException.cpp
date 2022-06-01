#include "FinalFullPathTooLongException.h"

namespace FileSystem
{
	FinalFullPathTooLongException::FinalFullPathTooLongException(const File* file, const std::string& filename) :
		FileSystemException("final full path must contain <= 255 symbols (including /'s)): " + std::to_string(file->getFullPath().size() + filename.size() + 1) + " > 255")
	{
	}
}

