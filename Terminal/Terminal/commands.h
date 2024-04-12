#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void purge();

void print(std::string message);
void time();
void showFolder(fs::path actualPath);
	
bool changeDir(std::string newPath, fs::path& savedPath);

bool makeDir(std::string nameDir);

bool delFolder(std::string nameDir);

bool moveFile(std::string fileToMove);
	

bool renameFile(std::string oldName);


bool makeFile(std::string name);

bool copyFile(std::string file);
	 

bool renameConsole(const std::string& name);

bool setColor(std::string color);

bool readFile(std::string fileName);

void help();

#endif

