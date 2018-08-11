#include "../include/Commands.h"


CdCommand::CdCommand(string _args):BaseCommand(_args){}

CdCommand::~CdCommand(){}

void CdCommand::execute(FileSystem & fs)
{
	string temp = getArgs();
	if (temp=="/")
		fs.setWorkingDirectory(&fs.getRootDirectory());
	else{
		BaseFile* dir = fs.returnLastElementInPath(temp); //this is the directory to move to
		Directory* d = dynamic_cast<Directory*>(dir);
		if (dir==nullptr || dir->isFile())// if the path isn't exists or the last element is file
			cout << "The system cannot find the path specified"<<endl;
		else
			fs.setWorkingDirectory(d);
	}
}

string CdCommand::toString()//prints the name of the command
{
	return "cd";
}
