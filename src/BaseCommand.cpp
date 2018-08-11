#include "../include/Commands.h"

BaseCommand::BaseCommand(string _args):args(_args){}

BaseCommand::~BaseCommand(){}

string BaseCommand:: getArgs() const
{
	return args;
}

void BaseCommand:: setArgs(string new_args)
{
	args = new_args;
}