#include "../include/Files.h"

BaseFile::BaseFile(string _name): name(_name){}

BaseFile::~BaseFile(){}

string BaseFile::getName() const
{
    return name;
}

void BaseFile::setName(string newName)
{
    name=newName;
}
