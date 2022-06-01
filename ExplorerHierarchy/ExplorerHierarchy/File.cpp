#include "File.h"
#include "NameContainsIllegalCharactersException.h"
#include "FinalFullPathTooLongException.h"

namespace FileSystem
{
	const size_t		File::MAX_PATH_LENGTH{ 255 };
	const char			File::SEPARATOR{ '/' };
	// \/:?*"<>|
	const std::regex	File::ILLEGAL_CHARACTERS{ "[\\\\/:?*<>| ]" };

	bool File::nameContainsIllegalCharacters(const std::string& filename) const
	{
		return (std::regex_search(filename, ILLEGAL_CHARACTERS));
	}

	bool File::finalFullPathLendthTooLong(const std::string& filename) const
	{
		return (fullPath.size() + 1 + filename.size()) > MAX_PATH_LENGTH;
	}

	File::File(const std::string& name, const size_t& size)
	{
		root = NULL;
		rename(name);
		fullPath = name;
		this->size = size;
		creationDate = time(0);
		changeDate = creationDate;
	}

	File* File::copy() const
	{
		if (isFolder())
		{
			return ((Folder*)this)->copy();
		}
		return new File(this->name, this->getSize());
	}

	const std::string& File::getName() const
	{
		return name;
	}

	const std::string& File::getFullPath() const
	{
		return fullPath;
	}

	bool File::isFolder() const
	{
		return false;
	}

	size_t File::getSize() const
	{
		return size;
	}

	void File::setRoot(Folder* root)
	{
		if (this->root)
		{
			this->root->remove(this->name);
		}
		this->root = root;
		fullPath = (root ? root->getFullPath() + SEPARATOR : "") + name;
	}

	const time_t& File::getCreationDate() const
	{
		return creationDate;
	}

	const time_t& File::getChangeDate() const
	{
		return changeDate;
	}

	Folder* File::getRoot()
	{
		return root;
	}

	std::string File::getInfo() const
	{
		return fullPath + " -> " + std::to_string(getSize()) + " bytes";
	}

	void File::rename(const std::string& name)
	{
		if (finalFullPathLendthTooLong(name))
		{
			throw FinalFullPathTooLongException(this, name);
		}
		if (nameContainsIllegalCharacters(name))
		{
			throw NameContainsIllegalCharactersException(name);
		}
		this->name = name;
		this->fullPath = (root ? root->getFullPath() : "") + SEPARATOR + name;
	}
}