#pragma once
#include <fstream>
#include <filesystem>

#if defined(__APPLE__) || defined(__linux__)
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#endif

class FileHandlingUtil
{
public:
	FileHandlingUtil() = delete;
	~FileHandlingUtil() = default;

	//Loads the text file at 'path' and stores text in 'text'
	//@param {std::string &} path The relative? path of the file to load
	//@param {std::string &} text The string to be filled with the file's text
	static void loadTextFile(const std::string & path, std::string & text);

	//Writes text file at 'path' with the contents 'text'
	//The file will be created if it does not already exist
	static void writeTextFile(const std::string & path, const std::string & text);

	//Get the users home directory
	//Supports compile on Windows, Linux, (TODO MacOS) using ifdef
	//Returns Documents folder on Windows
	//WARNING: NOT THREAD SAFE
	static void getHomeDirectory(std::string & home_dir_path);

	//Copy the file at the from path to the to path
	//Will create the necessary destination directories
	static void copyFile(const std::string & from, const std::string & to);

	//Creates directories given in path if they do not already exist
	static void createDirs(const std::string & path);

	//Returns true iff the path exists and is a file
	static bool doesFileExist(const std::string & path);

	//Get the filename of a path
	static std::string filenameFromPath(const std::string & path);

	//Get the parent path of a path
	static std::string parentPathFromPath(const std::string & path);
};
