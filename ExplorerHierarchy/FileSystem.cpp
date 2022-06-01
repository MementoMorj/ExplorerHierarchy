#include "FileSystem.h"
#include "UnknownFileTypeException.h"
#include "WrongFileSizeFormatException.h"
#include <iostream>

bool isPositiveNumber(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

std::istream& FileSystem::operator>>(std::istream& in, File*& file)
{
    std::string chunk;
    in >> chunk;
    if (chunk == "file")
    {
        chunk = "";
        in >> chunk;
        std::string sizeString;
        in >> sizeString;
        if (!isPositiveNumber(sizeString))
        {
            throw WrongFileSizeFormatException(sizeString);
        }
        file = new File(chunk, std::stoul(sizeString));
        return in;
    }
    if (chunk == "folder")
    {
        chunk = "";
        in >> chunk;
        file = new Folder(chunk);
        return in;
    }
    throw UnknownFileTypeException(chunk);
}
