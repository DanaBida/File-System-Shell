#include "../include/Commands.h"


LsCommand::LsCommand(string _args):BaseCommand(_args){
}

LsCommand::~LsCommand(){}

void LsCommand::execute(FileSystem & fs){

	string temp = getArgs();
	bool sortBySize = false;
	string firstWord = temp;
	if (fs.getStringUntilFirstSpace(temp)!="")
		firstWord = fs.getStringUntilFirstSpace(temp);
	if (firstWord=="-s"){ //check if we need to sort by size
		sortBySize=true;
		temp = fs.getStringAfterFirstSpace(temp); //delete [-s] so we remain with the path
	}
	Directory* current = &fs.getWorkingDirectory();
	if (temp.size()!=0)
		current = dynamic_cast<Directory*>(fs.returnLastElementInPath(temp));
	if (current!=nullptr){
		if (sortBySize)
			current->sortBySize();
		else
			current->sortByName();
		vectorPrint(current->getChildren());
	}
	else
		cout<<"The system cannot find the path specified"<<endl;
}

void LsCommand::vectorPrint(vector<BaseFile*> a){
    vector<BaseFile*>::const_iterator it;
    if (a.size()!=0)
	{
		for(it = a.begin(); it <= a.end()-1; it++)
		{
			if ((*it)->isFile())
				cout<<"FILE \t"<<(*it)->getName()<<"\t"<<(*it)->getSize()<<endl;
			else
				cout<<"DIR \t"<<(*it)->getName()<<"\t"<<(*it)->getSize()<<endl;
		}
    	}
}

string LsCommand::toString()//prints the name of the command
{
	return "ls";
}
