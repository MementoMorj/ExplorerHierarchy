#include "FileNameAlreadyTakenException.h"

namespace FileSystem
{
	FileNameAlreadyTakenException::FileNameAlreadyTakenException(const std::string& filename) :
		FileSystemException("filename \"" + filename + "\" is already taken")
	{

	}
}
