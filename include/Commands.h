#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include <iostream>

#include "Files.h"
#include "FileSystem.h"
#include "GlobalVariables.h"

using namespace std;


class BaseCommand {
private:
	string args;

public:
	BaseCommand(string args);
	virtual ~BaseCommand();
	string getArgs() const;
	virtual void execute(FileSystem & fs) = 0;
	virtual string toString() = 0;
	void setArgs(string new_args);

};

class PwdCommand : public BaseCommand {
private:
public:
	PwdCommand(string args);
	~PwdCommand();
	void execute(FileSystem & fs); // Every derived class should implement this function according to the document (pdf)
	virtual string toString();
};

class CdCommand : public BaseCommand {
private:
public:
	CdCommand(string args);
	~CdCommand();
	void execute(FileSystem & fs);
	string toString();
};

class LsCommand : public BaseCommand {
private:
public:
	LsCommand(string args);
	~LsCommand();
	void execute(FileSystem & fs);
	string toString();
	void vectorPrint(vector<BaseFile*> a);
};

class MkdirCommand : public BaseCommand {
private:
public:
	MkdirCommand(string args);
	~MkdirCommand();
	void execute(FileSystem & fs);
	string toString();
};

class MkfileCommand : public BaseCommand {
private:
public:
	MkfileCommand(string args);
	~MkfileCommand();
	void execute(FileSystem & fs);
	string toString();
};

class CpCommand : public BaseCommand {
private:
public:
	CpCommand(string args);
	~CpCommand();
	void execute(FileSystem & fs);
	string toString();
};

class MvCommand : public BaseCommand {
private:
public:
	MvCommand(string args);
	~MvCommand();
	void execute(FileSystem & fs);
	string toString();
};


class RenameCommand : public BaseCommand {
private:
public:
	RenameCommand(string args);
	~RenameCommand();
	void execute(FileSystem & fs);
	string toString();
};

class RmCommand : public BaseCommand {
private:
public:
	RmCommand(string args);
	~RmCommand();
	void execute(FileSystem & fs);
	string toString();
};

class HistoryCommand : public BaseCommand {
private:
	const vector<BaseCommand *> & history;
public:
	HistoryCommand(string args, const vector<BaseCommand *> & history);
	~HistoryCommand();
	void execute(FileSystem & fs);
	string toString();
};

class VerboseCommand : public BaseCommand {
private:
public:
	VerboseCommand(string args);
	~VerboseCommand();
	void execute(FileSystem & fs);
	string toString();
};

class ErrorCommand : public BaseCommand {
private:
public:
	ErrorCommand(string args);
	~ErrorCommand();
	void execute(FileSystem & fs);
	string toString();
};

class ExecCommand : public BaseCommand {
private:
	 const vector<BaseCommand *> & history;
public:
	ExecCommand(string args, const vector<BaseCommand *> & history);
	~ExecCommand();
	void execute(FileSystem & fs);
	string toString();
};


#endif
