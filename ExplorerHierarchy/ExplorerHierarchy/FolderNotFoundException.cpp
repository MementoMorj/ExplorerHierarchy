#include "FolderNotFoundException.h"

namespace FileSystem
{
	FolderNotFoundException::FolderNotFoundException(const std::string& foldername) :
		FileSystemException(std::string("folder with name \"") + foldername + "\" not found")
	{

	}
}
