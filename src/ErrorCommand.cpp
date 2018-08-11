#include "../include/Commands.h"


ErrorCommand::ErrorCommand(string _args):BaseCommand(_args){
}

ErrorCommand::~ErrorCommand(){}

void ErrorCommand::execute(FileSystem & fs)
{
	string temp = getArgs();
	string command = fs.getStringUntilFirstSpace(temp);
	if(command == "")// if there isn't any space
		cout<<temp<<": Unknown command"<<endl;
	else
		cout <<command<<": Unknown command"<<endl;
}

string ErrorCommand::toString()//prints the name of the command
{
	return "error";
}
