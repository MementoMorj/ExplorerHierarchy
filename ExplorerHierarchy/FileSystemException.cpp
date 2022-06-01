#include "FileSystemException.h"

namespace FileSystem
{
	FileSystemException::FileSystemException(const std::string& message)
	{
		text = message;
	}

	const std::string& FileSystemException::message() const
	{
		return text;
	}
}

