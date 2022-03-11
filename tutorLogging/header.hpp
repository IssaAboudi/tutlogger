//
// Created by ma422 on 11/25/2021.
//

#ifndef TUTORLOGGING_HEADER_HPP
#define TUTORLOGGING_HEADER_HPP

//INCLUDES:
#include <iostream>
#include <climits>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstring>
#include "DebugMode.hpp"

void clearCIN(void){
    //Clears Cin Buffer - ignores rest of input
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

std::string getDate(void){ //get only date in a string
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t printTime = std::chrono::system_clock::to_time_t(today);
    std::string dateTime = ctime(&printTime); //convert time to a string

    std::string date = dateTime.substr(0,10); //store only date
    std::string year = dateTime.substr(20,4); //get the year
    date += " ";
    date += year;
    return date;
}

std::string getDateTime(void){ //get both date and time in one string
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t printTime = std::chrono::system_clock::to_time_t(today);
    std::string dateTime = ctime(&printTime); //convert time to a string
    return dateTime;
}

std::string getTime(void){ //get only time in a string
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t printTime = std::chrono::system_clock::to_time_t(today);
    std::string dateTime = ctime(&printTime); //convert time to a string
    std::string time = dateTime.substr(11);
    return time;
}

std::pair<std::string, std::string> breakTime(std::string inString, char delim){
    //This function is about splitting a string into smaller strings using a specified delimiter.
    //For this program, I want the time to be split in two.
    //Left of the delimeter would be Hours and Right would be minutes


    std::vector<std::string> collection; //holds the broken up strings
    std::string part;

    std::pair<std::string, std::string> finalPair; //will be returned at the end

    //holds location of things in the string (start, end, delim etc)
    unsigned long startPos = 0; //references first character of the string
    unsigned long delimPos = 0; //references first delimiter
    unsigned long endPos = inString.size(); //references last character of string

    //initialize the positions
    if(inString.find(delim) == std::string::npos) { //if not found in string
        delimPos = inString.size(); //store pos last character in string
    } else {
        delimPos = inString.find(delim); //store pos where delim found in string
    }

    //Loop goes through the bigger string and breaks down each part of the string according to the delimiter
    do {
        if (startPos == endPos) { //if reached the end of the string
            break; //break out of the loop
        }
        part = inString.substr(startPos, delimPos - startPos); //stores part (leading up to the delim) in string
        if (delimPos + 1 < endPos){
            delimPos++; //moving one character past the delim in the string
        }
        startPos = delimPos; //stores next part after delim (leading up to next delim)
        if(inString.find(delim, delimPos) == std::string::npos) { //if not found in string
            delimPos = inString.size(); //store pos last character in string
        } else {
            delimPos = inString.find(delim, delimPos); //store pos where delim found in string
        }

        collection.push_back(part); //add part to the vector
    } while(delimPos != std::string::npos);

    //in this particular instance, we are only expecting two items to be added to the vector (hour and minute)
    finalPair = std::make_pair(collection[0], collection[1]);

    return finalPair;
}

void addNewSession(std::fstream &file, Student* student){
    std::string input = "";
    std::string numInput = "";
    while(input == "") {
        std::cout << "Please enter what subject you tutored in: "; //this could be unneccessary if everything is contained to Student objects
        std::getline(std::cin, input);
    }
    while(numInput == "") {
        std::cout << "How many minutes was your session?: ";
        std::getline(std::cin, numInput);
    }

    //edit student attributes;
    student->time += std::stoi(numInput);
    student->numSessions++;

    std::cout << "Time is: " << student->time << std::endl;
    int hour = std::stoi(numInput) / 60;
    int min = std::stoi(numInput) % 60;

    file << getDate() << " : " << student->name << " -> " << input << " - " << hour << " hour(s) and " << min << " minutes";
    file << std::endl;
}

void addNewSession(std::fstream &file, float &time, Student* student){
    std::string input;
    std::cout << "Please enter what subject you tutored in: ";
    std::getline(std::cin, input);

    student->time += time;
    student->numSessions++;

    int hour = (int)time / 60;
    int min = (int)time % 60;

    //TODO: add tutee name to the file
    //TODO: write out total hours of tutoring
    file << getDate() << " : " << student->name << " -> " << input << " - " << hour << " hour(s) and " << min << " minutes";
    file << std::endl;
}

void timeSession(std::fstream &file, Student* student){
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    std::string input;

    start = std::chrono::system_clock::now(); //records begin time
    std::cout << "Press any key when you reach the end of your session" << std::endl;
    while (!std::cin.get()) { /*Just waits for end of session*/}
    end = std::chrono::system_clock::now(); //records end time

    std::chrono::duration<float> duration = end - start; //calculate duration
    float minutes = std::chrono::duration_cast<std::chrono::seconds>(duration).count() / 60;
    LOG("timeSession: " << minutes);

    addNewSession(file, minutes, student); //adds to log file
}

void addTutee(const std::string &filePath, std::vector<Student> &students) {
    std::string input;
    Student temp;

    SPACER();

    std::cout << "Add Tutee: " << std::endl;
    std::cout << "-=-=-=-=-=-" << std::endl;
    std::cout << "Enter Tutee name: ";
    std::getline(std::cin, input);
    temp.name = input;

    std::cout << "Enter Tutee Subject: "; //TODO: Make this more robust - what about multiple subjects?
    std::getline(std::cin, input);
    temp.subject = input;

    students.push_back(temp);
    updateRecords(filePath, students);

    SPACER();
}

void listStudents(std::vector<Student> &students){
    if(students.size() < 1){
        return;
    }
    SPACER();
    std::cout << "Your Tutees" << std::endl;
    std::cout << "-=-=-=-=-=-" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        std::cout << i << " : " << students[i] << std::endl;
    }
    SPACER();
}

Student* selectTutee(std::vector<Student> &students){
    int menuInput;
    Student* student;

    listStudents(students);
    std::cout << "Please select a tutee for the session: " << std::endl;
    std::cout << ">> ";
    std::cin >> menuInput;
    clearCIN();

    SPACER();

    student = &students[menuInput];
    return student;
}

//TODO: add edit tutee function
// - tutor should be able to correct or adjust any attributes of their students
// - Won't affect the actual log but will correct data stored about tutee
// - - Like # of sessions. If accidentally added an extra session, they can correct that

#endif //TUTORLOGGING_HEADER_HPP
