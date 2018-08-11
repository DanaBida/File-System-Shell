#include "../include/FileSystem.h"

FileSystem::FileSystem(): rootDirectory(new Directory("/", nullptr)), workingDirectory(rootDirectory)
{}

FileSystem:: ~FileSystem()
{
	if(verbose == 3 || verbose == 1)
		cout<<"FileSystem:: ~FileSystem()"<<endl;


	workingDirectory = nullptr;
	delete rootDirectory;
}

FileSystem::FileSystem(const FileSystem& other): rootDirectory(&(other.getRootDirectory())), workingDirectory (&(other.getWorkingDirectory()))
{
	if(verbose == 3 || verbose == 1)
		cout<<"FileSystem::FileSystem(const FileSystem& other)"<<endl;

    copyFileSystem(other);
}//copy constructor


FileSystem& FileSystem::operator=(const FileSystem& other)//copy assignment operator
{
	if(verbose == 3 || verbose == 1)
		cout<<"FileSystem& FileSystem::operator=(const FileSystem& other)"<<endl;

    if(this!=&other)
    {
        cleanFileSystem();
        copyFileSystem(other);
    }
    return *this;
}

FileSystem::FileSystem(FileSystem&& other): rootDirectory(&(other.getRootDirectory())),workingDirectory(&(other.getWorkingDirectory()))
{
	if(verbose == 3 || verbose == 1)
		cout<<"FileSystem::FileSystem(FileSystem&& other)"<<endl;

	other.rootDirectory= nullptr;
	other.workingDirectory= nullptr;
}//move constructor


FileSystem& FileSystem::operator=(FileSystem&& other)
{
	if(verbose == 3 || verbose == 1)
		cout<<"FileSystem& FileSystem::operator=(FileSystem&& other)"<<endl;

	cleanFileSystem();
    rootDirectory=&(other.getRootDirectory());
	workingDirectory=&(other.getWorkingDirectory());
    other.rootDirectory= nullptr;
    other.workingDirectory= nullptr;
    return *this;
}//move assignment operator


void FileSystem:: copyFileSystem(const FileSystem& other){

	rootDirectory=new Directory("/",nullptr);
    string path = other.getWorkingDirectory().getAbsolutePath();
    workingDirectory = dynamic_cast<Directory*>(returnLastElementInPath(path));

}

void FileSystem:: cleanFileSystem(){

	delete this;
}

Directory& FileSystem:: getRootDirectory() const
{
    return *rootDirectory;
}

Directory& FileSystem:: getWorkingDirectory() const
{
    return *workingDirectory;
}

void FileSystem:: setWorkingDirectory(Directory *newWorkingDirectory)
{
    workingDirectory = newWorkingDirectory;
}




string FileSystem:: getStringUntilFirstSpace(string s)
//if the string don't have space - returns "".
{
	size_t space_position= s.find(" ",0); //finds the first space, to know where the word ends
	if(space_position==string::npos)
		return "";
	return s.substr(0, space_position); //returns word without the space
}

string FileSystem:: getStringAfterFirstSpace(string s)
//if the string don't have space - returns "".
{
	string temp=getStringUntilFirstSpace(s);
	if(temp == "")
		return temp;
	else
	{
		size_t size=temp.size();
		return s.substr(size+1); //returns the word without the space
	}
}

string FileSystem:: getFirstWordInPath(string path)
//returns the first word in the path (after the first slash if exists), and deletes the root is exists in path
//if the path is empty(after the starting directory) - returns "".
{
	if (path.size()==0) //if the string is empty
		return "";
	if(path.substr(0,0)=="/")
		path = path.substr(1);
	size_t slashAfterBaseFile=path.find_first_of("/");
	string firstBaseFile;
	if(slashAfterBaseFile!=string::npos)
		firstBaseFile = path.substr(0,slashAfterBaseFile);
	else
		firstBaseFile = path;
	return firstBaseFile;
}

string FileSystem:: getPathWithoutFirstWord(string path)
//returns the path after first word (and after the first slash if exists).
//if the path only have one word - returns "".
{
	if (path.find("/")==string::npos) //word have no slashes
		return "";
	else{
	string firstWordInpath = getFirstWordInPath(path);
//	if(firstWordInpath !="" && path[firstWordInpath.size()+1]!=string::npos) not sure why do we need this?
	if (path.at(0)=='/')
		return path.substr(firstWordInpath.size()+2);
	else
		return path.substr(firstWordInpath.size()+1);
	}
}

string FileSystem:: getLastWordInPath (string path)
//returns the last word (file/directory) in path. for example, input: d1/d2/d3/file, return: file.
//if the path is empty(after the starting directory) - returns "".
{
	if (path.size()==0) //if the string is empty
		return "";
	size_t lastSlash=path.find_last_of("/");
	if(lastSlash == string::npos)
		return path;
	else
		return path.substr(lastSlash+1);
}

string FileSystem:: getPathWithoutLastWord (string path)
//returns the last word (file/directory) in path. for example, input: d1/d2/d3/file, return: d1/d2/d3
//if the path is empty(after the starting directory) or the path contain one word only - returns "".
//useful when getting paths to a file, and wants to enter the folder where the file is.
{
	if (path.size()==0) //if the string is empty
		return "";
	size_t lastSlash=path.find_last_of("/");
	if(lastSlash == string::npos)
		return "";
	else
	{
		size_t lastSlash=path.find_last_of("/");
		return path.substr(0,lastSlash);
	}
}

Directory* FileSystem:: returnStartingDirectory (string& path)
//sets the filesystem starting directory, and returns the directory
//if path begins with slash, set to root and delete the slash
//if not, set to working directory
{
    Directory* startingDir = workingDirectory;
    if (path.at(0)=='/')
    {
        startingDir = rootDirectory;
        path = path.substr(1);//deletes the "\"
    }
    return startingDir;
}

BaseFile* FileSystem::returnLastElementInPath(string path)
//gets a path. if exist, returns the last folder, else returns nullptr.
{
    if (path=="/")
    	return dynamic_cast<BaseFile*>(&this->getRootDirectory());
	Directory* current= returnStartingDirectory(path);
    string dir_name=getFirstWordInPath(path);
	while (path!="")
	{
		if(dir_name==" ")
		{
			current= returnStartingDirectory(path);
			dir_name = getFirstWordInPath(getStringAfterFirstSpace(path));
			path=getPathWithoutFirstWord(path);
		}
		if (dir_name=="..")
		{
			if (current->getName()!="/")//if we're not in root folder
			{
				current=current->getParent();
				if (dir_name==path) //path is one word, which means we reached the last word in path
					return current;
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			BaseFile* bf=returnBaseFileIfExist(*current, dir_name);
			if (bf==nullptr)//folder does not exist
				return nullptr;
			if (dir_name==path) //path is one word, which means we reached the last word in path
				return bf;
			else
				current = dynamic_cast<Directory*>(bf);
		}
		//move forward in path
		path=getPathWithoutFirstWord(path);
		dir_name = getFirstWordInPath(path);
	}
	return nullptr;
}

BaseFile* FileSystem:: returnBaseFileIfExist(Directory& nameOfContainerDirectory, string name)
//gets a directory and a basefile name. Returns the file if it exists, else returns nullptr.
{
	vector<BaseFile*> c = nameOfContainerDirectory.getChildren();
    vector<BaseFile*>::const_iterator it;
    for(it = c.begin() ; it < c.end() ; it++)
    	if((*it)->getName()==name)
    		return *it;
    return nullptr;
}

Directory* FileSystem:: returnDirectoryIfExist(Directory& nameOfContainerDirectory, string name)
//solution to bug where returnBaseLine will only return file in case of file and directory in same name, allowing to create duplicate directories
{
	vector<BaseFile*> c = nameOfContainerDirectory.getChildren();
    vector<BaseFile*>::const_iterator it;
    for(it = c.begin() ; it < c.end() ; it++)
    	if((*it)->getName()==name){
    		const bool ans = (*it)->isFile();
    		if (!ans)
    			return dynamic_cast<Directory*>(*it);
    	}
    return nullptr;
}

File* FileSystem:: returnFileIfExist(Directory& nameOfContainerDirectory, string name)
//like returnDirectory but opposite
{
	vector<BaseFile*> c = nameOfContainerDirectory.getChildren();
    vector<BaseFile*>::const_iterator it;
    for(it = c.begin() ; it < c.end() ; it++)
    	if((*it)->getName()==name){
    		const bool ans = (*it)->isFile();
    		if (ans)
    			return dynamic_cast<File*>(*it);
    	}
    return nullptr;
}
