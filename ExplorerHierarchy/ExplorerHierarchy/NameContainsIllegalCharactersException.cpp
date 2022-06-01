#include "NameContainsIllegalCharactersException.h"

namespace FileSystem
{
	NameContainsIllegalCharactersException::NameContainsIllegalCharactersException(const std::string& filename) :
		FileSystemException("filename \"" + filename + "\" contains illegal character(s)")
	{
	}
}