#include "../include/Commands.h"


PwdCommand::PwdCommand(string _args):BaseCommand(_args){
}

PwdCommand::~PwdCommand(){}


void PwdCommand::execute(FileSystem & fs){
	cout<< fs.getWorkingDirectory().getAbsolutePath() <<endl;
}

string PwdCommand::toString()//prints the name of the command
{
	return "pwd";
}
