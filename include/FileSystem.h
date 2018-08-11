#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Files.h"

using namespace std;

class FileSystem {
private:
	Directory* rootDirectory;
	Directory* workingDirectory;
public:
	FileSystem();
	Directory& getRootDirectory() const; // Return reference to the root directory
	Directory& getWorkingDirectory() const; // Return reference to the working directory
	void setWorkingDirectory(Directory *newWorkingDirectory); // Change the working directory o
	~FileSystem();//destructor
	FileSystem(const FileSystem& other);//copy constructor
	FileSystem& operator=(const FileSystem& other);//copy assignment operator
	FileSystem(FileSystem&& other);//move constructor
	FileSystem& operator=(FileSystem&& other);//move assignment operator
	void copyFileSystem(const FileSystem& other);
	void cleanFileSystem();
	void stealFileSystem(FileSystem& other);

	string getStringUntilFirstSpace(string s); //gets the first word of a string, separated by space
	string getStringAfterFirstSpace(string s); //deletes the first word of a string, separated by space
	string getFirstWordInPath(string path); //gets the first Directory in a path
	string getLastWordInPath (string path); //returns the name of the last word in path
	string getPathWithoutLastWord (string path); //return the path without the last word
	string getPathWithoutFirstWord(string path); //return the path without the first word
    BaseFile* returnLastElementInPath(string path); //gets a path and returns the last element if exists, nullptr if not.
    Directory* returnStartingDirectory (string& path);//returns the starting directory in path - root if it begins in "/" , and working otherwise
    BaseFile* returnBaseFileIfExist(Directory& nameOfContainerDirectory, string name);//returns pointer to file if the Container Directory contains file, else returns null.
    Directory* returnDirectoryIfExist(Directory& nameOfContainerDirectory, string name);//returns pointer to file if the Container Directory contains file, else returns null.
    File* returnFileIfExist(Directory& nameOfContainerDirectory, string name);//returns pointer to file if the Container Directory contains file, else returns null.


};


#endif
