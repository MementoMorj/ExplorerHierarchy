#include "IllegalMoveDestinationException.h"

namespace FileSystem
{
	IllegalMoveDestinationException::IllegalMoveDestinationException() :
		FileSystemException("attempt to move a folder in the deeper one")
	{
	}
}

