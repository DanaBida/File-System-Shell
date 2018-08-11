#include "../include/Files.h"
#include <algorithm>



Directory::Directory(string name, Directory *_parent): BaseFile(name), children(), parent(_parent) //constructor
{}

Directory::~Directory()//destructor - remove Directory recursively
{
	if(verbose == 3 || verbose == 1)
			cout<<"Directory::~Directory()"<<endl;

	for(vector<BaseFile*>::iterator it = children.begin(); it != children.end() ; it++)
			delete *it;
}

Directory& Directory::operator=(const Directory& other)//copy assignment operator
{
	if(verbose == 3 || verbose == 1)
			cout<<"Directory& Directory::operator=(const Directory& other)"<<endl;

    if(this!=&other)
    {
    	delete this;
    	copyDirectory(other);
    }
    return *this;
}

Directory::Directory(Directory&& other): BaseFile(other.getName()), children(other.children), parent(other.parent)//move constructor
{
	if(verbose == 3 || verbose == 1)
		cout<<"Directory::Directory(Directory&& other)"<<endl;

	(other.children).clear();
	other.parent = nullptr;
}

Directory& Directory::operator=(Directory&& other)//move assignment operator
{
	if(verbose == 3 || verbose == 1)
		cout<<"Directory& Directory::operator=(Directory&& other)"<<endl;

	delete this;
    stealDirectory(other);
    return *this;
}

Directory::Directory(const Directory& other): BaseFile(other.getName()), children(), parent(other.parent) //copy constructor - copy the directory recursively
{
	if(verbose == 3 || verbose == 1)
		cout<<"Directory::Directory(const Directory& other)"<<endl;

	copyDirectory(other);
	parent = nullptr;
}

void Directory:: copyDirectory(const Directory& other)
{
	setName(other.getName());
	vector<BaseFile*>::const_iterator it;
	for(it= (other.children).begin() ; it < other.children.end() ; it++)
	{
		BaseFile* b;
		if ((**it).isFile())
		{
			File* f = dynamic_cast<File*>(*it);
			b = new File(*f);
			children.push_back(b);
		}

		else
		{
			Directory* d = dynamic_cast<Directory*>(*it);
			b = new Directory(*d);
			dynamic_cast<Directory*>(b)->setParent(this);
		}
	}
}


void Directory::stealDirectory(Directory& other)
{
	setParent(other.parent);
	children = other.children;
	(other.children).clear();
	other.parent = nullptr;
}

Directory* Directory::getParent() const
{
    return parent;
}

void Directory::setParent(Directory* newParent)
{
	Directory* oldParent=parent;
    parent = newParent;
    newParent->children.push_back(this);

    //remove the directory from the old parent
    if (oldParent!=nullptr)
    	oldParent->removeFile(this);
}

void Directory:: addFile(BaseFile* file)
{
	if(returnBaseFileIfExist(file->getName())==nullptr)//if The file isn't exists in the directory
	{
		if((*file).isFile())
			children.push_back(file);
		else
		{
			Directory* d = dynamic_cast<Directory*>(file);
			d->setParent(this);
		}
	}
}

void Directory:: removeFile(string _name)
{
	bool found =false;
    vector<BaseFile*>::iterator it;
    for(it = children.begin(); it <= children.end()-1  && !found ; it++)//moving forword until find the pos of name
    	if((*it)->getName() == _name)
    		found =true;
    if(found)//if file exists, delete it
    {
        delete(*it);
        children.erase (it);
    }
}

void Directory::removeFile(BaseFile* file)
{
	bool found =false;
    vector<BaseFile*>::iterator it;
    vector<BaseFile*>::iterator it2;

    for(it = children.begin(); it <= children.end()-1 && !found ; it++)//moving forward until find the pos of file
    	if((*it)->getName() == file->getName()){
    	    found =true;
    	    it2=it;
    	}
    if(found)//if file exists, delete it
    {
        delete file;
        children.erase (it2);
    }
}

vector<BaseFile*> Directory:: getChildren()
{
    return children;
}

void Directory:: sortBySize()
{
	 sort(children.begin(), children.end(), compareBySize);
}

bool Directory:: compareBySize(BaseFile* b1, BaseFile* b2)
{
	return (b1->getSize() < b2->getSize());
}

void Directory:: sortByName()
{
	sort(children.begin(), children.end(),  compareByName);
}

bool Directory:: compareByName(BaseFile* b1, BaseFile* b2)
{
	return (b1->getName() < b2->getName());
}

int Directory:: getSize()
{
	if(children.size()==0)
		return 0;
	else
	{
		vector<BaseFile*>::const_iterator it = children.begin();
	    return getSizeRecursively(children,it);
	}
}

int Directory:: getSizeRecursively (const vector<BaseFile*>& v1, vector<BaseFile*>::const_iterator it)
{
	if(it==children.end()-1){
        return (*it)->getSize();
    }
    return (*it)->getSize() + getSizeRecursively(children,++it);
}

string Directory:: getAbsolutePath()
{
	//we assume all folders are children of root - no 'floating' folders.
	if (this->getName()=="/")
		return "/";
	else{
		string AbsPath = "/" + getName();
		Directory* p = parent;
		while(p->getName()!="/"){
			AbsPath.insert(0, "/" + p->getName());
			p = p->parent;
		}
		return AbsPath;
	}
}

bool Directory:: isFile() const
{
	return false;
}

bool Directory::operator==(const Directory& other){
	string s1=this->getAbsolutePath();
	Directory other2 = other;
	string s2=other2.getAbsolutePath();
	if (this->getName()==other.getName() && (s1.compare(s2)==0))
		return true;
	else
		return false;
}

BaseFile* Directory:: returnBaseFileIfExist(string name)
//gets a directory and a basefile name. Returns the file if it exists, else returns nullptr.
{
	if (children.size()>0){
		vector<BaseFile*>::const_iterator it;
		for(it = children.begin(); it <= children.end()-1 ; ++it)
		{
			if((*it)->getName()==name)
				return (*it);
		}
	}
    return nullptr;
}


