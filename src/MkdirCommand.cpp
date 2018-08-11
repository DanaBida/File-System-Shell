#include "../include/Commands.h"

MkdirCommand::MkdirCommand(string args):BaseCommand(args)//constructor
{}

MkdirCommand:: ~MkdirCommand(){}


void MkdirCommand::execute(FileSystem & fs)
{
    bool isAllPathExists= true;
    string temp = getArgs();
    BaseFile* startingDir= fs.returnStartingDirectory(temp);
    while(temp.size()!=0)
    {
        string dir_name= fs.getFirstWordInPath(temp);
        temp = fs.getPathWithoutFirstWord(temp);
        if(startingDir->isFile())
        {
            	cout<<"The directory already exists"<<endl;
       		isAllPathExists=false;
 	        temp="";
        }
        else
        {
        	//check if the first directory exists
        	Directory* directoryFound = fs.returnDirectoryIfExist(*dynamic_cast<Directory*>(startingDir), dir_name);
        	File* fileFound = fs.returnFileIfExist(*dynamic_cast<Directory*>(startingDir), dir_name);
        	if (directoryFound== nullptr && fileFound==nullptr)//if first directory doesn't exists, creates it
        	{
        	     isAllPathExists=false;
        	     directoryFound = new Directory(dir_name,nullptr);
        	     directoryFound->setParent(dynamic_cast<Directory*>(startingDir));
        	}
            if (directoryFound!= nullptr)
            	startingDir=directoryFound;
            else if (fileFound!= nullptr)
                startingDir=fileFound;
        }
    }

    if(isAllPathExists)
        cout<<"The directory already exists"<<endl;

}

string MkdirCommand::toString()//prints the name of the command
{
    return "mkdir";
}
