//
// Created by ma422 on 11/25/2021.
//

#ifndef TUTORLOGGING_APPLICATION_HPP
#define TUTORLOGGING_APPLICATION_HPP

//INCLUDES:
#include <iostream>
#include <climits>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstring>
#include "Student.hpp"
#include "Files/files.hpp"
#include "Ext/imgui/imgui.h"
 #include "DebugMode.hpp"

#define NUM_ACTIVE_STUDENTS 20


namespace tutlogger {
    void processFiles(std::vector<Student> &tutees);

    void createWindow(std::vector<Student> &tutees, Student** f_tutees);

    void tutorialWindow();

    Status updateFile(Student** f_tutees, std::vector<Student>&tutees);
}

void clearCIN(void);

std::string getDate(void);

std::string getDateTime(void);

std::string getTime(void);

std::pair<std::string, std::string> breakTime(std::string inString, char delim);

void addNewSession(std::fstream &file, Student* student);

void addNewSession(std::fstream &file, float &time, Student* student);

void timeSession(std::fstream &file, Student* student);

void addTutee(const std::string &filePath, std::vector<Student> &students);

void listStudents(std::vector<Student> &students);

Student* selectTutee(std::vector<Student> &students);

void consoleApp();

//TODO: add edit tutee function
// - tutor should be able to correct or adjust any attributes of their students
// - Won't affect the actual log but will correct data stored about tutee
// - - Like # of sessions. If accidentally added an extra session, they can correct that

#endif //TUTORLOGGING_APPLICATION_HPP
