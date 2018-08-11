#include "../include/Environment.h"
#include "../include/Commands.h"


ExecCommand::ExecCommand(string _args, const vector<BaseCommand *> &history):BaseCommand(_args), history (history)
{}

ExecCommand:: ~ExecCommand(){}

void ExecCommand::execute(FileSystem & fs)
{
	const char * s= getArgs().c_str();
	unsigned long i = atol(s);
	if(i >= history.size())
		cout<<"Command not found"<<endl;
	else{
		string command_type = history.at(i)->toString();
		string _args = history.at(i)->getArgs();
		BaseCommand* command;
		_args=fs.getStringAfterFirstSpace(_args); //delete the command name from the beginning of the path
		if(command_type=="pwd")
			command = new PwdCommand(_args);
		else if(command_type=="cd")
			command = new CdCommand(_args);
		else if(command_type=="ls")
			command = new LsCommand(_args);
		else if(command_type=="mv")
			command = new MvCommand(_args);
		else if(command_type=="cp")
			command = new CpCommand(_args);
		else if(command_type=="rename")
			command = new RenameCommand(_args);
		else if(command_type=="mkdir")
			command = new MkdirCommand(_args);
		else if(command_type=="mkfile")
			command = new MkfileCommand(_args);
		else if(command_type=="rm")
			command = new RmCommand(_args);
		else if(command_type=="verbose")
			command = new VerboseCommand(_args);
		else if(command_type=="history")
			command = new HistoryCommand(_args, commandsHistory);
		else
			command = new ErrorCommand(_args);
		command->execute(fs);
	}
}

string ExecCommand::toString()//prints the name of the command
{
	return "exec";
}
