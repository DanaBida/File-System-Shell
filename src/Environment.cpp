#include "../include/Environment.h"


Environment::Environment(): commandsHistory(), fs()
{}

void Environment::start()
{
	string _args="temp";
	BaseCommand* command;
	//input new command
	cout<<fs.getWorkingDirectory().getAbsolutePath()<<"> ";
	getline(cin, _args);
	while (_args!="exit")
	{
		if (verbose==2 || verbose==3)
			cout<<fs.getWorkingDirectory().getAbsolutePath()<<"> "<<_args<<endl;
		string command_type= getFirstWord(_args);
		string original_args = _args; //save this for error command
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
		else if(command_type=="exec")
			command = new ExecCommand(_args, commandsHistory);
		else
			command = new ErrorCommand(original_args);
		command->execute(fs);
		command->setArgs(command->toString() + " " + command->getArgs()); //return the command name, to add to history
		addToHistory(command);
		//input new command
		cout<<fs.getWorkingDirectory().getAbsolutePath()<<"> ";
		getline(cin, _args);
	}
	if (verbose==2 || verbose==3)
		cout<<fs.getWorkingDirectory().getAbsolutePath()<<"> "<<endl;

}


Environment:: ~Environment()//destructor
{
	if(verbose == 3 || verbose == 1)
		cout<<"Environment:: ~Environment()"<<endl;

	clearEnvironment();
}

void Environment:: clearEnvironment ()
{
	vector<BaseCommand*>::iterator it;
	for(it = commandsHistory.begin() ; it != commandsHistory.end() ; ++it)
		delete (*it);
	commandsHistory.clear();
}

Environment::Environment(const Environment& other): commandsHistory(), fs()//copy constructor
{
	if(verbose == 3 || verbose == 1)
		cout<<"Environment::Environment(const Environment& other)"<<endl;

	copyEnvironment(other);
}

void Environment:: copyEnvironment (const Environment& other)
{
	fs.setWorkingDirectory(&other.fs.getWorkingDirectory());//?????
    vector<BaseCommand*>::const_iterator it;
    for ( it = other.commandsHistory.begin() ; it < other.commandsHistory.end() ; it++)
    {
    	string _args = (*it)->getArgs();
    	string command_type= getFirstWord(_args);
		BaseCommand* command;
		if(command_type.compare("pwd")==0)
			command = new PwdCommand(_args);
		else if(command_type.compare("cd"))
			command = new CdCommand(_args);
		else if(command_type.compare("ls"))
			command = new LsCommand(_args);
		else if(command_type.compare("mv"))
			command = new MvCommand(_args);
		else if(command_type.compare("cp"))
			command = new CpCommand(_args);
		else if(command_type.compare("rename"))
			command = new RenameCommand(_args);
		else if(command_type.compare("mkdir"))
			command = new MkdirCommand(_args);
		else if(command_type.compare("mkfile"))
			command = new MkfileCommand(_args);
		else if(command_type.compare("rm"))
			command = new RmCommand(_args);
		else if(command_type.compare("verbose"))
			command = new VerboseCommand(_args);
		else if(command_type.compare("history"))
			command = new HistoryCommand(_args, other.commandsHistory);
		else if(command_type.compare("exec"))
			command = new ExecCommand(_args, other.commandsHistory);
		else
			command = new ErrorCommand(_args);
		addToHistory(command);
    }
}

Environment& Environment::operator=(const Environment& other)//copy assignment operator
{
	if(verbose == 3 || verbose == 1)
		cout<<"Environment& Environment::operator=(const Environment& other)"<<endl;

    if(this!=&other)
    {
    	clearEnvironment ();
    	copyEnvironment(other);
    }
    return *this;
}

Environment::Environment(Environment&& other): commandsHistory(other.commandsHistory), fs(other.fs)//move constructor
{
	if(verbose == 3 || verbose == 1)
		cout<<"Environment::Environment(Environment&& other)"<<endl;

	(other.commandsHistory).clear();
}

Environment& Environment::operator=(Environment&& other)//move assignment operator
{
	if(verbose == 3 || verbose == 1)
		cout<<"Environment& Environment::operator=(Environment&& other)"<<endl;

    if(this!=&other)
    {
    	clearEnvironment();
    	stealEnvironment(other);
    }
    return *this;
}

void Environment::stealEnvironment(Environment& other)
{
	commandsHistory = other.commandsHistory;
	fs = other.fs;
	(other.commandsHistory).clear();
}


FileSystem& Environment::getFileSystem()
{
	return fs;
}

void Environment::addToHistory(BaseCommand *command)
{
	commandsHistory.push_back(command);
}

const vector<BaseCommand*>& Environment::getHistory() const
{
	return commandsHistory;
}

string Environment:: getFirstWord(string s)
{
	size_t space_position= s.find(" ",0); //finds the first space, to know where the word ends
	return s.substr(0, space_position);
}

void Environment:: vectorPrint(vector<BaseFile*> a){
    vector<BaseFile*>::const_iterator it;
    cout<<"the files in the vector are: "<<endl;
    for(it = a.begin(); it <= a.end()-1; it++)
    	cout<<(*it)->getName()<<", size: "<<(*it)->getSize()<<endl;
}
