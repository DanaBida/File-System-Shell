#include "../include/Commands.h"


HistoryCommand::HistoryCommand(string _args, const vector<BaseCommand *> & _history): BaseCommand(_args), history(_history)
{}

HistoryCommand:: ~HistoryCommand(){}

void HistoryCommand::execute(FileSystem & fs)
{
	if(history.size()!=0)// if the history command list isn't empty
	{
		vector<BaseCommand*>::const_iterator it;
		int counter=0;//contains the number of the current commend.
		for(it = history.begin(); it <= history.end()-1; it++)
		{
			cout<<counter<<"\t"<<(*it)->getArgs()<<endl;
			counter++;
		}
	}

}

string HistoryCommand::toString()//prints the name of the command
{
	return "history";
}
