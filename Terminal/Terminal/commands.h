#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

typedef std::string string;

void purge();

void print(string message);
void time();
void showFolder(fs::path actualPath);
	
bool changeDir(string newPath, fs::path& savedPath);

bool makeDir(string nameDir);

bool delFolder(string nameDir);

bool moveFile(string fileToMove);
	

bool renameFile(string oldName);


bool makeFile(string name);

bool copyFile(string file);
	 

bool renameConsole(const string& name);

bool setColor(string color);

bool readFile(string fileName);

void help();

#endif

