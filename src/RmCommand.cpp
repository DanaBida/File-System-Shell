#include "../include/Commands.h"

RmCommand:: RmCommand(string args): BaseCommand(args)
{}

RmCommand:: ~RmCommand()
{}

void RmCommand:: execute(FileSystem & fs)
{

	string path = getArgs();
	if(fs.returnLastElementInPath(path)==nullptr)
		cout<<"No such file or directory"<<endl;
	else
	{
		bool is_ok=true;
		if((path=="/") || path==(fs.getWorkingDirectory()).getAbsolutePath())
		{
			cout<<"Can't remove directory"<<endl;
			is_ok=false;
		}	
		bool isParentWorking = false;
		//check if one of the directories in the path is a parent of working directory
		if(fs.returnStartingDirectory(path) == &(fs.getRootDirectory()))
		{
			Directory* start= &fs.getRootDirectory();
			string temp = path;
			while(temp.size()!=0)
			{
				string dir_name = fs.getFirstWordInPath(temp);
				if(fs.returnBaseFileIfExist(*start, dir_name)==(fs.getWorkingDirectory()).getParent())
					isParentWorking = true;
				start =dynamic_cast<Directory*> (fs.returnBaseFileIfExist(*start,fs.getFirstWordInPath(temp)));
				temp = fs.getPathWithoutFirstWord(temp);
			}
		}
		if(isParentWorking)
		{
			cout<<"Can't remove directory"<<endl;
			is_ok=false;
		}
		if (is_ok)
		{
			BaseFile* needToBeRemoved = fs.returnLastElementInPath(path);
			Directory* source_path;
			if (needToBeRemoved->getName() == path)
				source_path = &fs.getWorkingDirectory();
			else
			{
				path=fs.getPathWithoutLastWord(path);
				source_path = dynamic_cast<Directory*>(fs.returnLastElementInPath(path));
			}
			source_path->removeFile(needToBeRemoved);
		}
	}
}

string RmCommand:: toString(){
	return "rm";
}


