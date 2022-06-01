#pragma once
#include <regex>

namespace FileSystem
{
	class File;
	class Folder;
}

namespace FileSystem
{
	class File
	{
	public:
		static const char	SEPARATOR;
	private:
		static const size_t			MAX_PATH_LENGTH;
		
		static const std::regex		ILLEGAL_CHARACTERS;

		Folder*		root;
		std::string name;
		std::string fullPath;
		size_t		size;
		time_t		creationDate;
		time_t		changeDate;

		
	protected:
		bool nameContainsIllegalCharacters(const std::string& filename) const;
		bool finalFullPathLendthTooLong(const std::string& filename) const;

	public:
		File(const std::string& name, const size_t& size);

		File* copy() const;

		const std::string& getName() const;
		const std::string& getFullPath() const;

		virtual bool isFolder() const;
		virtual size_t getSize() const;

		Folder* getRoot();
		void setRoot(Folder* root);

		const time_t& getCreationDate() const;
		const time_t& getChangeDate() const;

		virtual std::string getInfo() const;

		void rename(const std::string& name);
	};
	
	std::istream& operator>>(std::istream& in, File*& file);
}

namespace FileSystem
{
	class Folder :
		public File
	{
	private:
		std::vector<File*> files;
		std::vector<File*>::iterator findFileIteratorByName(const std::string& filename);
		bool fileNameAlreadyTaken(const std::string& filename) const;
	public:
		Folder(const std::string& name);

		File* findFileByName(const std::string& filename);
		Folder* findFolderByName(const std::string& filename);
		Folder* findFolderByPath(const std::string& path);

		virtual bool isFolder() const;

		Folder* copy() const;

		std::string getInfo() const override;

		void createFolder(const std::string& name);
		size_t getSize() const override;

		void rename(const std::string& filename, const std::string& newName);

		Folder* get(std::string filename);
		void add(File* file);
		void remove(const std::string& filename);
		std::string display() const;
	};
}