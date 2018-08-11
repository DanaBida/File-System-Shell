# All Targets
all: fs


fs: bin/Main.o bin/File.o bin/BaseFile.o bin/Directory.o bin/FileSystem.o bin/BaseCommand.o bin/CdCommand.o bin/CpCommand.o bin/ErrorCommand.o  bin/LsCommand.o  bin/MkdirCommand.o bin/MkfileCommand.o bin/MvCommand.o bin/PwdCommand.o bin/RenameCommand.o bin/RmCommand.o bin/VerboseCommand.o bin/Environment.o bin/ExecCommand.o bin/HistoryCommand.o
	g++ -o bin/fs bin/Main.o bin/BaseFile.o  bin/File.o  bin/Directory.o bin/FileSystem.o bin/BaseCommand.o bin/CdCommand.o bin/PwdCommand.o bin/LsCommand.o bin/VerboseCommand.o bin/ErrorCommand.o bin/MkdirCommand.o bin/MkfileCommand.o bin/RmCommand.o bin/MvCommand.o bin/CpCommand.o bin/RenameCommand.o bin/Environment.o bin/ExecCommand.o bin/HistoryCommand.o


# Depends on the source and header files 
bin/Main.o: src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp
	
bin/BaseFile.o: src/BaseFile.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BaseFile.o src/BaseFile.cpp

bin/Directory.o: src/Directory.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Directory.o src/Directory.cpp
	
bin/File.o: src/File.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/File.o src/File.cpp

bin/FileSystem.o: src/FileSystem.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/FileSystem.o src/FileSystem.cpp
	
bin/BaseCommand.o: src/BaseCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BaseCommand.o src/BaseCommand.cpp
	
bin/CdCommand.o: src/CdCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/CdCommand.o src/CdCommand.cpp
		
bin/CpCommand.o: src/CpCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/CpCommand.o src/CpCommand.cpp
		
bin/MvCommand.o: src/MvCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MvCommand.o src/MvCommand.cpp
		
bin/PwdCommand.o: src/PwdCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/PwdCommand.o src/PwdCommand.cpp
	
bin/LsCommand.o: src/LsCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/LsCommand.o src/LsCommand.cpp
	
bin/RenameCommand.o: src/RenameCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/RenameCommand.o src/RenameCommand.cpp
		
bin/MkfileCommand.o: src/MkfileCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MkfileCommand.o src/MkfileCommand.cpp
		
bin/MkdirCommand.o: src/MkdirCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MkdirCommand.o src/MkdirCommand.cpp
		
bin/ErrorCommand.o: src/ErrorCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ErrorCommand.o src/ErrorCommand.cpp
	
bin/ExecCommand.o: src/ExecCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ExecCommand.o src/ExecCommand.cpp
		
bin/HistoryCommand.o: src/HistoryCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/HistoryCommand.o src/HistoryCommand.cpp
		
bin/VerboseCommand.o: src/VerboseCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/VerboseCommand.o src/VerboseCommand.cpp	
			
bin/RmCommand.o: src/RmCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/RmCommand.o src/RmCommand.cpp	

bin/Environment.o: src/Environment.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Environment.o src/Environment.cpp


#Clean the build directory
clean: 
	rm -f bin/*

