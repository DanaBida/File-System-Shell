#include "../include/Files.h"

File::File(string name, int size) : BaseFile(name), size(size)
{}

File::~File(){
	if(verbose == 3 || verbose == 1)
		cout<<"File::~File()"<<endl;

}//destructor

int File:: getSize()
{
    return size;
}

bool File:: isFile() const
{
	return true;
}

File::File(const File& other): BaseFile(other.getName()), size(other.size) //copy constructor
{
	if(verbose == 3 || verbose == 1)
		cout<<"File::File(const File& other)"<<endl;
}

File& File::operator=(const File& other)//copy assignment operator
{
	if(verbose == 3 || verbose == 1)
		cout<<"File& File::operator=(const File& other)"<<endl;
    if(this!=&other){
    	delete this;
    	copyFile(other);
    }
    return *this;
}

File::File(File&& other): BaseFile(other.getName()), size(other.size)	//move constructor
{
	if(verbose == 3 || verbose == 1)
		cout<<"File::File(File&& other)"<<endl;
}

File& File::operator=(File&& other)	//move assignment operator
{
	if(verbose == 3 || verbose == 1)
		cout<<"File::File& operator=(File&& other)"<<endl;
	return *this;
}

void File::copyFile(const File& other)
{
	setName(other.getName());
	size=other.size;
}

