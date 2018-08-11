#include "../include/Commands.h"


CpCommand::CpCommand(string _args):BaseCommand(_args){
}

CpCommand::~CpCommand(){}

void CpCommand::execute(FileSystem & fs)
{
	//enter folder of first file
	string temp = getArgs();
	string source_path = fs.getStringUntilFirstSpace(temp); //paths have no spaces, so first word is first path
	if(source_path != "")// if the path with spaces
	{
		BaseFile* file_to_copy= fs.returnLastElementInPath(source_path); //this is the item to copy
		string destination_path = fs.getStringAfterFirstSpace(temp);
		BaseFile* destination = fs.returnLastElementInPath(destination_path);// this is the directory to copy to
		Directory* destination_dir = dynamic_cast<Directory*>(destination);
		if (file_to_copy==nullptr || destination==nullptr || destination->isFile())
			cout<<"No such file or directory"<<endl;
		else
			if (file_to_copy->isFile())
			{
				File* f = new File (*(dynamic_cast<File*>(file_to_copy))); //call copy constructor
				destination_dir->addFile(f);
			}
			else
			{
				Directory* d = new Directory(*(dynamic_cast<Directory*>(file_to_copy))); //call copy constructor
				destination_dir->addFile(d);
			}

	}

}

string CpCommand::toString()//prints the name of the command
{
    return "cp";
}
