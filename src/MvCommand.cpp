#include "../include/Commands.h"


MvCommand::MvCommand(string _args):BaseCommand(_args){
}

MvCommand::~MvCommand(){}

void MvCommand::execute(FileSystem & fs)
{
	//enter folder of first file
	string temp = getArgs();
	string source_path = fs.getStringUntilFirstSpace(temp); //paths have no spaces, so first word is first path
	BaseFile* file_to_move= fs.returnLastElementInPath(source_path); //this is the item to move
	string name_file_to_move = fs.getLastWordInPath(source_path);
	if (source_path!=name_file_to_move && fs.getPathWithoutLastWord(source_path).size()>0)
		source_path = fs.getPathWithoutLastWord(source_path);

	else
		if (fs.getPathWithoutLastWord(source_path).size()==0)
			source_path="/";
	Directory* source_directory;
	if (name_file_to_move == source_path)
		source_directory = &fs.getWorkingDirectory();

	else
		source_directory = dynamic_cast<Directory*>(fs.returnLastElementInPath(source_path));
	string destination_path = fs.getStringAfterFirstSpace(temp);
	BaseFile* destination = fs.returnLastElementInPath(destination_path);
	Directory* destination_dir = dynamic_cast<Directory*>(destination);
	if (file_to_move==nullptr || destination==nullptr || destination->isFile())
		cout<<"No such file or directory"<<endl;
	else
		if(file_to_move == &(fs.getRootDirectory()) || file_to_move == &(fs.getWorkingDirectory()) || file_to_move == (fs.getWorkingDirectory()).getParent()|| fs.returnBaseFileIfExist(*destination_dir,name_file_to_move)!=nullptr)
			cout<<"Can't move directory"<<endl;
		else
		{
			if (file_to_move->isFile())
			{
				File* f = new File (*(dynamic_cast<File*>(file_to_move))); //call copy constructor
				destination_dir->addFile(f);
			}
			else
			{
				Directory* d = new Directory(*(dynamic_cast<Directory*>(file_to_move))); //call copy constructor
				destination_dir->addFile(d);
			}
			source_directory->removeFile(file_to_move);
		}

}

string MvCommand::toString()//prints the name of the command
{
    return "mv";
}
