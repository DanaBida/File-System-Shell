#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>
#include <iostream>
#include "GlobalVariables.h"

using namespace std;

class BaseFile {
private:
	string name;
	
public:
	BaseFile(string name);
	virtual ~BaseFile();
	string getName() const;
	void setName(string newName);
	virtual int getSize() = 0;
	virtual bool isFile() const = 0;

};

class File : public BaseFile {
private:
	int size;
		
public:
	File(string name, int size); // Constructor
	int getSize(); // Return the size of the file
	bool isFile() const;
	~File();//destructor
	File(const File& other);//copy constructor
	File& operator=(const File& other);//copy assignment operator
	File(File&& other);//move constructor
	File& operator=(File&& other);//move assignment operator
	void copyFile(const File& other);
};

class Directory : public BaseFile {
private:
	vector<BaseFile*> children;
	Directory *parent;

public:
	Directory(string name, Directory *parent); // Constructor
	Directory *getParent() const; // Return a pointer to the parent of this directory
	void setParent(Directory *newParent); // Change the parent of this directory
	void addFile(BaseFile* file); // Add the file to children
	void removeFile(string name); // Remove the file with the specified name from children
	void removeFile(BaseFile* file); // Remove the file from children
	vector<BaseFile*> getChildren(); // Return children
	int getSize(); // Return the size of the directory (recursively)

	void sortByName(); // Sort children by name alphabetically (not recursively)
	void sortBySize(); // Sort children by size (not recursively)
	string getAbsolutePath();  //Return the path from the root to this
	bool operator==(const Directory& other);
	bool isFile() const;
	BaseFile* returnBaseFileIfExist(string name);//returns pointer to directory if the Container Directory contains directory, else returns null.

	~Directory();//destructor
	Directory(const Directory& other);//copy constructor
	Directory& operator=(const Directory& other);//copy assignment operator
	Directory(Directory&& other);//move constructor
	Directory& operator=(Directory&& other);//move assignment operator
	void copyDirectory(const Directory& other);
	void stealDirectory(Directory& other);
	int getSizeRecursively (const vector<BaseFile*>& children, vector<BaseFile*>::const_iterator it);//help function to getSize
	static bool compareBySize(BaseFile* b1, BaseFile* b2); /*compares the size of two BaseFiles.
															returns true if first is smaller than second*/
	static bool compareByName(BaseFile* b1, BaseFile* b2); /*compares the name of two BaseFiles.
															returns true if first is smaller than second*/
};

#endif
