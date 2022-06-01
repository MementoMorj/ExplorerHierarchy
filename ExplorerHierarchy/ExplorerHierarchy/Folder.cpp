#include "FileSystem.h"
#include "NameContainsIllegalCharactersException.h"
#include "FileNameAlreadyTakenException.h"
#include "FinalFullPathTooLongException.h"
#include "FolderNotFoundException.h"
#include "FileNotFoundException.h"
#include <numeric>
#include <regex>
#include <sstream>

//const std::string PICTURE_NEEDED_CHARACTERS{ "[]()+{}." };
//const std::string ILLEGAL_MASK_CHARACTERS{ "[\[\]()+{}]" };
//
//bool containsIllegalMaskCharacters(const std::string& text)
//{
//	return (std::regex_search(text, std::regex(ILLEGAL_MASK_CHARACTERS)));
//}
//
//std::string picturize(const char& symbol)
//{
//	if (symbol == '?')
//	{
//		return std::string(".");
//	}
//	if (symbol == '*')
//	{
//		return std::string(".*");
//	}
//	if (PICTURE_NEEDED_CHARACTERS.find(symbol) != PICTURE_NEEDED_CHARACTERS.npos)
//	{
//		return std::string({ '\\', symbol });
//	}
//	return std::string({ symbol });
//}
//
//std::regex maskToRegex(const std::string& mask)
//{
//	std::string regexString;
//	for (const char& symbol : mask)
//	{
//		regexString += picturize(symbol);
//	}
//	return std::regex(regexString);
//}

namespace FileSystem
{
	bool Folder::fileNameAlreadyTaken(const std::string& filename) const
	{
		return std::any_of(files.begin(), files.end(),
			[&filename](const File* file)
			{
				return file->getName() == filename;
			}
		);
	}

	std::vector<File*>::iterator Folder::findFileIteratorByName(const std::string& filename)
	{
		std::vector<File*>::iterator fileIterator = std::find_if(files.begin(), files.end(),
			[&filename](const File* file)
			{
				return file->getName() == filename;
			});
		if (fileIterator == files.end())
		{
			throw FileNotFoundException(filename);
		}
		return fileIterator;
	}

	File* Folder::findFileByName(const std::string& filename)
	{
		std::vector<File*>::iterator it = std::find_if(files.begin(), files.end(),
			[&filename](const File* file)
			{
				return (filename == file->getName());
			});
		if (it == files.end())
		{
			throw FileNotFoundException(filename);
		}
		return files[std::distance(files.begin(), it)];
	}

	Folder* Folder::findFolderByName(const std::string& filename)
	{
		std::vector<File*>::iterator it = std::find_if(files.begin(), files.end(),
			[&filename](const File* file)
			{
				return (file->isFolder()) && (filename == file->getName());
			});
		if (it == files.end())
		{
			throw FolderNotFoundException(filename);
		}
		return (Folder*)files[std::distance(files.begin(), it)];
	}

	Folder* Folder::findFolderByPath(const std::string& path)
	{
		size_t separatorPosition = path.find(SEPARATOR);
		if (separatorPosition == path.npos)
		{
			return findFolderByName(path);
		}
		std::string nextFolderName = path.substr(0, separatorPosition);
		return findFolderByName(nextFolderName)->findFolderByPath(path);
	}

	Folder::Folder(const std::string& name) :
		File(name, 0)
	{
	}

	bool Folder::isFolder() const
	{
		return true;
	}

	Folder* Folder::copy() const
	{
		Folder* folder = new Folder(getName());
		std::for_each(files.begin(), files.end(),
			[&folder](const File* file)
			{
				if (file->isFolder())
				{
					folder->add(((Folder*)file)->copy());
					return;
				}
				folder->add(file->copy());
			});
		return folder;
	}

	std::string Folder::getInfo() const
	{
		return getFullPath() + " -> contains " + std::to_string(files.size()) + " files -> " + std::to_string(getSize()) + " bytes";
	}

	void Folder::createFolder(const std::string& name)
	{
		Folder folder(name);
		add(&folder);
	}

	size_t Folder::getSize() const
	{
		return std::accumulate(files.begin(), files.end(), size_t(),
			[](const size_t size, const File* file)
			{
				return size + file->getSize();
			});
	}

	void Folder::rename(const std::string& filename, const std::string& newName)
	{
		std::vector<File*>::iterator fileIterator = findFileIteratorByName(filename);
		try
		{
			findFileIteratorByName(newName);
		}
		catch (const FileNotFoundException&)
		{
			(*fileIterator)->rename(newName);
			return;
		}
		throw FileNameAlreadyTakenException(newName);
	}

	Folder* Folder::get(std::string filename)
	{
		return findFolderByName(filename);
	}

	void Folder::add(File* file)
	{
		const std::string filename = file->getName();
		if (fileNameAlreadyTaken(filename))
		{
			throw FileNameAlreadyTakenException(filename);
		}
		files.push_back(file);
		file->setRoot(this);
	}

	void Folder::remove(const std::string& filename)
	{
		if (nameContainsIllegalCharacters(filename))
		{
			throw NameContainsIllegalCharactersException(filename);
		}
		files.erase(findFileIteratorByName(filename));
	}

	std::string Folder::display() const
	{
		return getInfo() + std::accumulate(files.begin(), files.end(), std::string(),
			[](const std::string& text, const File* file)
			{
				return text + "\n" + file->getInfo();
			});
	}
}