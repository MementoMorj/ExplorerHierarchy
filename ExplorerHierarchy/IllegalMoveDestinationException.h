#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
	class IllegalMoveDestinationException :
		public FileSystemException
	{
	public:
		IllegalMoveDestinationException();
	};
}
