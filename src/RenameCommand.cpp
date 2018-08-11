#include "../include/Commands.h"


RenameCommand::RenameCommand(string _args):BaseCommand(_args){}

RenameCommand::~RenameCommand(){}

void RenameCommand::execute(FileSystem & fs)
{
	string temp = getArgs();
	string source_path = fs.getStringUntilFirstSpace(temp); //paths have no spaces, so first word is first path
	BaseFile* to_rename= fs.returnLastElementInPath(source_path); //this is the file we need to rename
	if (to_rename==nullptr)
		cout<<"No such file or directory"<<endl;
	else
	{
		BaseFile* baseFile_directory;
		//if the path contain only one basefile to rename or: "/" + one basefile
		if (source_path == ("/"+to_rename->getName()) || source_path == to_rename->getName())
		{
			if(source_path == to_rename->getName())
				baseFile_directory = &fs.getWorkingDirectory();
			else
				baseFile_directory = &fs.getRootDirectory();
		}
		else
		{
			string temp2= fs.getPathWithoutLastWord(temp);
			baseFile_directory= fs.returnLastElementInPath(temp2); //this is the file we need to rename
		}
		Directory* directoryContains_to_rename= dynamic_cast<Directory*>(baseFile_directory);
		string new_name = fs.getStringAfterFirstSpace(temp);//second word of the path is the needed name;
		if(to_rename==&fs.getWorkingDirectory())
			cout << "Can't rename the working directory"<<endl;
		if (to_rename!=&fs.getWorkingDirectory() && to_rename!=&fs.getRootDirectory() && fs.returnBaseFileIfExist(*directoryContains_to_rename,new_name)==nullptr)
				to_rename->setName(new_name);
	}
}

string RenameCommand::toString()//prints the name of the command
{
	return "rename";
}
