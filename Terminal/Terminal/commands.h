#pragma once

#include <ctime>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <Windows.h>
namespace fs = std::filesystem;


//clear terminal command
void purge() { std::cout << "\033[2J\033[1;1H"; }

//print something in the terminal (print is removed)
void print(std::string message) {
	try {
		std::cout << message.substr(6) << "\n";
	}
	catch (std::exception& e) {
		std::cerr << "PrintError : No content.";
	}
}

//Show the current time
void time() {
	std::time_t currentTime = time(nullptr);
	std::tm* timeInfo = std::localtime(&currentTime);

	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d / %H:%M:%S", timeInfo);
	std::cout << "The current time : " << buffer << "\n";
}


//Show all the folder where the user is located
void showFolder(fs::path actualPath) {
	try {
		//browse the actualPath
		for (const auto& entry : fs::directory_iterator(actualPath)) {
			//check if it is a regular file
			if (fs::is_regular_file(entry)) {
				std::cout << "File : " << entry.path() << "\n";
			}
			//check if it is a directory
			else if (fs::is_directory(entry)) {
				std::cout << "Directory : " << entry.path() << "\n";
			}
		}
	}
	//ERROR MANAGEMENT 
	catch (const std::exception& e) {
		// e.what() -> show the error
		std::cerr << "Error accessing directory : " << e.what() << "\n";
	}

}

//Change the directory
bool changeDir(std::string newPath, fs::path& savedPath) {
	try {
		//remove 'gt' -> get the path without the command
		newPath = newPath.substr(3);
		fs::current_path(newPath);
		savedPath = fs::current_path();
		return true;
	}
	//error management
	catch (std::exception) {
		std::cerr << "DirectoryError : The requested file could not be found.\n";
		return false;
	}



}

bool makeDir(std::string nameDir) {
	try {
		nameDir = nameDir.substr(6);
		if (fs::exists(nameDir)) {
			std::cout << "The file already exists.\n";
			return false;
		}
		if (fs::create_directory(nameDir)) {
			std::cout << nameDir << " has been created successfully.\n";
			return true;
		}

	}
	catch (std::exception& e) {
		std::cerr << "FileCreationError :" << e.what() << std::endl;
		return false;
	}






}

bool delFolder(std::string nameDir) {
	try {
		nameDir = nameDir.substr(5);
		if (fs::exists(nameDir)) {
			//delete all directory / file
			fs::remove_all(nameDir);
			std::cout << nameDir << " has been deleted successfully.";
			return true;
		}
		//if the spelling is false
		else std::cout << nameDir << " is not a file, check the spelling.\n"; return false;
	}
	//error management
	catch (std::exception& e) {
		std::cerr << "FileDeleteError : " << e.what() << std::endl;
		return false;
	}
}

bool moveFile(std::string fileToMove) {
	//newDirectory / input C:\Users\amogu\Desktop\iMAGE
	std::string newDirectoryInput;
	try {
		//get file name
		fileToMove = fileToMove.substr(3);

		fs::path file(fileToMove);

		// check if file exists
		if (fs::exists(file)) {
			std::cout << "Where do you want to move " << file.filename() << "> ";
			std::getline(std::cin >> std::ws, newDirectoryInput);
			// check if new dir exists
			if (fs::exists(newDirectoryInput)) {


				fs::path newDirectory(newDirectoryInput);
				fs::rename(file, newDirectory / file.filename());
				std::cout << "moved successfully";
				return true;


			}

			//if path doesn't exist
			std::cout << "Error! : \n-Path to move the file doesn't exist.\n";
			return false;
		}

		// if file does not exist
		std::cout << "Error! : \n-File to move doesn't exist.\n";
		return false;

	}
	catch (std::exception& e) {
		std::cerr << "File moving error : " << e.what() << "\n";
	}
}

bool renameFile(std::string oldName) {
	try {
		oldName = oldName.substr(4);
		std::string newName;
		if (fs::exists(oldName)) {
			std::cout << "New file / Directory name (with extension)  : ";
			std::getline(std::cin >> std::ws, newName);
			fs::rename(oldName, newName);
			std::cout << oldName << " has been renamed successfully.";
			return true;

		}
		else {
			std::cout << "Error : 2 possibilites : \n-The initial file doesn't exist.\n-Wrong spelling initial file.\n";
			return false;
		}

	}
	catch (std::exception& e) {
		std::cerr << "File naming error : " << e.what() << "\n";
		return false;
	}
}

bool makeFile(std::string name) {
	try {
		name = name.substr(4);
		std::ofstream mkFile(name);
		if (mkFile.is_open()) {
			std::cout << "File created successfully";
			mkFile.close();
			return true;
		}
	}
	catch (std::exception& e) {
		std::cerr << "File creating error : " << e.what() << "\n";
		return false;
	}
}

bool copyFile(std::string file) {
	std::string newFdir;
	try {
		file = file.substr(4);
		if (fs::exists(file)) {
			std::cout << "New directory : ";
			std::getline(std::cin >> std::ws, newFdir);

			if (fs::exists(newFdir) && fs::is_directory(newFdir)) {
				fs::path sourcePath(file);
				fs::path destinationPath(newFdir);
				fs::copy(sourcePath, destinationPath / sourcePath.filename());
				std::cout << "The file has been copied successfully\n";
				return true;
			}
		}
		else {
			std::cout << "File or directory doesn't exist.";
			return false;
		}
	}
	catch (std::exception& e) {
		std::cerr << "File copying error : " << e.what() << "\n";
		return false;
	}

}

bool renameConsole(const std::string& name) {
	try {
		SetConsoleTitleA(name.substr(8).c_str());
		return true;
	}
	catch (std::exception& e) {
		std::cerr << "RenameConsoleError : " << e.what() << "\n";
		return false;
	}

}

bool setColor(std::string color) {
	try {
		color = color.substr(6);
		int colorInt = std::stoi(color);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, colorInt);
		return true;
	}
	catch (std::exception& e) {
		std::cerr << "SetColorError : " << e.what() << "\n";
		return false;
	}

}

bool readFile(std::string fileName) {
	try {
		fileName = fileName.substr(3);

		std::fstream file(fileName.c_str());
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				std::cout << line << std::endl;
			}
			return true;
		}
		else {
			std::cout << "File doesn't exit ? \n";
			return false;
		}
	}
	catch (std::exception& e) {
		std::cerr << "ReadFileError" << e.what() << "\n";
		return false;
	}

}

void help() {
	std::cout << "----------------Command Help----------------\n\n";
	std::cout << "purge -> clear the terminal.\n";
	std::cout << "print + message -> print a message.\n";
	std::cout << "mkdir + name -> create a directory.\n";
	std::cout << "delf + name -> delete a directory.(with its content!)\n";
	std::cout << "gt + directory -> change the current path.\n";
	std::cout << "sfd -> show all file in the current directory.\n";
	std::cout << "time -> Show the current time.\n";
	std::cout << "rnf + file / path -> rename the file.\n";
	std::cout << "mv + file / path -> move the file.\n";
	std::cout << "mkf + file -> create a file\n";
	std::cout << "renamec + name -> change the console name.\n";
	std::cout << "color + number -> change the console color.\n";
	std::cout << "rf + file name -> read the file content. \n";
	std::cout << "exit -> close the program.\n";
	std::cout << "\n---------------------------------------------\n";
}
