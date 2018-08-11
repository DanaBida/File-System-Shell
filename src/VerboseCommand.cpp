#include "../include/Commands.h"



VerboseCommand::VerboseCommand(string _args):BaseCommand(_args){}

VerboseCommand:: ~VerboseCommand(){}

void VerboseCommand::execute(FileSystem & fs)
{
	int num = atoi(getArgs().c_str());
	if (num>=0 && num <=3)
		::verbose=num;
	else
		cout<<"Wrong verbose input"<<endl;
}

string VerboseCommand::toString()//prints the name of the command
{
	return "verbose";
}
