
#include <iostream>
#include <filesystem>
#include <string>
#include "commands.h"
#include <Windows.h>
namespace fs = std::filesystem;





int main() {
    SetConsoleTitle(TEXT("Bouminal-Console"));
    std::cout << "BouMinal [version 0.1]" << std::endl;
    //path where the program is located
    fs::path path = fs::current_path();

    std::string action;
    while (true) {
        //User input
        std::cout << "\n" << path.string() << "> ";
        std::getline(std::cin >> std::ws, action);



        if (action == "purge") purge();
        else if (action._Starts_with("print")) print(action);
        else if (action == "exit") break;
        else if (action == "time") time();
        else if (action == "sfd") showFolder(path);
        else if (action._Starts_with("gt")) changeDir(action, path);
        else if (action._Starts_with("mkdir")) makeDir(action);
        else if (action._Starts_with("delf")) delFolder(action);
        else if (action._Starts_with("mv")) moveFile(action);
        else if (action._Starts_with("rnf")) renameFile(action);
        else if (action._Starts_with("mkf")) makeFile(action);
        else if (action._Starts_with("cp")) copyFile(action);
        else if (action._Starts_with("renamec")) renameConsole(action);
        else if (action._Starts_with("color")) setColor(action);
        else if (action._Starts_with("rf")) readFile(action);
        else if (action == "help") help();
        else std::cout << "'" << action << "' is not recognized by bouminal.";
    }


    return 0;
}