
#ifndef TUTORLOGGING_FILES_HPP
#define TUTORLOGGING_FILES_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include "../DebugMode.hpp"
#include "../Ext/json.hpp"

//Student Data Structure association with files

struct student {
public:
    std::string name = "";
    std::string subject = "";
    int numSessions = 0;

    //Functions with OS Specific Implementations:


    friend std::ostream& operator<<(std::ostream &fs, const student &rval)  {
        fs << rval;
        return fs;
    }
};

//Function definition depends on operating systems.
//See:
// files_windows.cpp - for Windows
// files_linux.cpp - for Linux/Unix based OS's
// files_mac.cpp - for Mac OS X (all) //TODO: Add definition for Mac OS
//============================
//Returns a filepath (OS specific) to create folders & files
std::string getFilePath();

//creates a folder in provided filepath
bool createFolder(const std::string &filePath);
//TODO: add Windows and Mac Implementation

void updateLog(const std::string &filePath, std::vector<student> students);
//TODO: add Windows and Mac Implementation

//TODO: add pull from log function to fill up vector to use in main

#endif //TUTORLOGGING_FILES_HPP
