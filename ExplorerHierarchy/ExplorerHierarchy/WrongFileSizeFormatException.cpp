#include "WrongFileSizeFormatException.h"

namespace FileSystem
{
	WrongFileSizeFormatException::WrongFileSizeFormatException(std::string& sizeString) :
		FileSystemException(std::string("wrong format of file size: \"") + sizeString + "\"")
	{
	}
}

