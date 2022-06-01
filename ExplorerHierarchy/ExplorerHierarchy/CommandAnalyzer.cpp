#include "CommandAnalyzer.h"
#include "UnknownCommandException.h"
#include "NoRootException.h"
#include "IllegalMoveDestinationException.h"
#include <sstream>
#include <numeric>
#include <string>

namespace FileSystem
{
	CommandAnalyzer::CommandAnalyzer(std::istream& in)
	{
		this->in = &in;
	}

	void CommandAnalyzer::analyze()
	{
		std::cout << currentFolder->getFullPath() + ">";
		std::string fullCommandLine;
		getline(*in, fullCommandLine);
		std::stringstream commandStream(fullCommandLine);
		std::string command;
		getline(commandStream, command, ' ');
		try
		{
			if (command == "get")
			{
				std::string filename;
				commandStream >> filename;
				currentFolder = currentFolder->get(filename);
				return analyze();
			}
			if (command == "getbypath")
			{
				std::string path;
				commandStream >> path;
				currentFolder = currentFolder->findFolderByPath(path);
				return analyze();
			}
			if (command == "new")
			{
				File* file;
				commandStream >> file;
				currentFolder->add(file);
				return analyze();
			}
			if (command == "del")
			{
				std::string filename;
				commandStream >> filename;
				currentFolder->remove(filename);
				return analyze();
			}
			if (command == "up")
			{
				if (currentFolder->getRoot() == NULL)
				{
					throw NoRootException();
				}
				currentFolder = currentFolder->getRoot();
				return analyze();
			}
			if (command == "display")
			{
				std::cout << currentFolder->display() << "\n";
				return analyze();
			}
			if (command == "move")
			{
				std::string filename;
				commandStream >> filename;
				File* file = currentFolder->findFileByName(filename);
				std::string path;
				commandStream >> path;
				if (file->isFolder() &&
					std::regex_match(path, std::regex(file->getFullPath())))
				{
					throw IllegalMoveDestinationException();
				}
				Folder* destinationFolder = &mainFolder;
				if (path == "")
				{
					destinationFolder->add(file);
					return analyze();
				}
				size_t firstPos = path.find('/');
				if (firstPos != 0)
				{
					throw IllegalMoveDestinationException();
				}
				destinationFolder = destinationFolder->findFolderByPath(path.substr(1, path.length()));
				destinationFolder->add(file);
				return analyze();
			}
			if (command == "copy")
			{
				std::string filename;
				commandStream >> filename;
				File* file = currentFolder->findFileByName(filename);
				std::string path;
				commandStream >> path;
				if (file->isFolder() &&
					std::regex_match(path, std::regex(file->getFullPath())))
				{
					throw IllegalMoveDestinationException();
				}
				Folder* destinationFolder = &mainFolder;
				if (path == "")
				{
					destinationFolder->add(file->copy());
					return analyze();
				}
				size_t firstPos = path.find(File::SEPARATOR);
				if (firstPos != 0)
				{
					throw IllegalMoveDestinationException();
				}
				destinationFolder = destinationFolder->findFolderByPath(path.substr(1, path.length()));
				destinationFolder->add(file->copy());
				return analyze();
			}
			if (command == "rename")
			{
				std::string filename;
				commandStream >> filename;
				std::string newName;
				commandStream >> newName;
				currentFolder->rename(filename, newName);
				return analyze();
			}
			if (command == "cls")
			{
				system("cls");
				return analyze();
			}
			if (command == "exit")
			{
				return;
			}
			throw UnknownCommandException(command);
		}
		catch (const FileSystemException& e)
		{
			std::cout << "error: " + e.message() + "\n";
			return analyze();
		}
	}
}