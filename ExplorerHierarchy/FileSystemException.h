#pragma once
#include "FileSystem.h"

namespace FileSystem
{
	class FileSystemException
	{
	private:
		std::string text;
	public:
		FileSystemException(const std::string& message);

		const std::string& message() const;
	};
}


