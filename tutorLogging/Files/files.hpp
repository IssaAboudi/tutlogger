
#ifndef TUTORLOGGING_FILES_HPP
#define TUTORLOGGING_FILES_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include "../DebugMode.hpp"
#include "../Ext/json.hpp"
#include "../student.hpp"

//Function definition depends on operating systems.
//See:
// files_windows.cpp - for Windows
// files_linux.cpp - for Linux/Unix based OS's
// files_mac.cpp - for Mac OS X (all) //TODO: Add definition for Mac OS

//===============================================
//Returns a filepath (OS specific) to create folders & files
std::string getFilePath();

//creates a folder in provided filepath
bool createFolder(const std::string &filePath);
//TODO: add Windows and Mac Implementation

//===============================================

//All non-dependent definitions are found in:
// files_all.cpp


/* JSON FILES */
void updateRecords(const std::string &filePath, std::vector<student> students);
// stores tutee information locally (on disk)

void loadRecords(const std::string &filePath, std::vector<student> &students);
// loads in tutee information from disk

/* TEXT FILES */
void makeLog(const std::string &filePath, std::fstream &inputFile);
//creates the log text file for tutors

#endif //TUTORLOGGING_FILES_HPP
