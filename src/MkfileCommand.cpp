#include "../include/Commands.h"

MkfileCommand:: MkfileCommand(string args): BaseCommand(args)
{}

MkfileCommand:: ~MkfileCommand(){}


void MkfileCommand:: execute(FileSystem & fs)
{

	string temp = getArgs();
    string path = fs.getStringUntilFirstSpace(temp); //path
    string file_name=fs.getLastWordInPath(path); //name of new file
    Directory* directory_to_add=fs.returnStartingDirectory(path);
    path=fs.getPathWithoutLastWord(path); //path of directory to add new file
    if (path.size()>0)
    	directory_to_add = dynamic_cast<Directory*>(fs.returnLastElementInPath(path)); //directory to add file to
    string file_size = fs.getStringAfterFirstSpace(temp);
    //creates new file if needed
    if(directory_to_add==nullptr)//if the path to the file doesn't exists
         cout<<"The system cannot find the path specified"<<endl;
    else
    {
    	File* isFilefound=fs.returnFileIfExist(*directory_to_add, file_name);
    	Directory* isDirectoryfound=fs.returnDirectoryIfExist(*directory_to_add, file_name);
    	if(isFilefound || isDirectoryfound)
    		cout<<"File already exists"<<endl;
    	else
    	{
    		//if file doesn't exist creates it
    		File* file = new File(file_name,atoi(file_size.c_str()));
    		directory_to_add->addFile(file);
    	}    }
}


string MkfileCommand:: toString(){

    return "mkfile";
}
