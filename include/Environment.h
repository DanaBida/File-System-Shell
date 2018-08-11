#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Files.h"
#include "Commands.h"
#include "GlobalVariables.h"
#include "FileSystem.h"

#include <string>
#include <vector>

using namespace std;

class Environment {
private:
	vector<BaseCommand*> commandsHistory;
	FileSystem fs;

public:
	Environment();
	void start();
	FileSystem& getFileSystem() ; // Get a reference to the file system
	void addToHistory(BaseCommand *command); // Add a new command to the history
	const vector<BaseCommand*>& getHistory() const; // Return a reference to the history of commands

	static string getFirstWord(string s); //gets the first word of a string, separated by space

	~Environment();//destructor
	Environment(const Environment& other);//copy constructor
	Environment& operator=(const Environment& other);//copy assignment operator
	Environment(Environment&& other);//move constructor
	Environment& operator=(Environment&& other);//move assignment operator
	void clearEnvironment ();
	void stealEnvironment(Environment& other);
	void copyEnvironment (const Environment& other);
	void vectorPrint(vector<BaseFile*> a);
};

#endif
