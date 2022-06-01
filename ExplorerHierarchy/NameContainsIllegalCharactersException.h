#pragma once
#include "FileSystemException.h"

namespace FileSystem
{
    class NameContainsIllegalCharactersException :
        public FileSystemException
    {
    public:
        NameContainsIllegalCharactersException(const std::string& filename);
    };
}
