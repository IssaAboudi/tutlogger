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

std::string getDate(void){
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t printTime = std::chrono::system_clock::to_time_t(today);
    std::string dateTime = ctime(&printTime); //convert time to a string
    std::string date = dateTime.substr(0,10); //store only date
    std::string year = dateTime.substr(20,4);
    date += " ";
    date += year;
    return date;
}

std::string getDateTime(void){
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t printTime = std::chrono::system_clock::to_time_t(today);
    std::string dateTime = ctime(&printTime); //convert time to a string
    return dateTime;
}

std::string getTime(void){
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

void addNewSession(std::fstream &file){
    std::string input;
    std::string numInput;
    std::cout << "Please enter what subject you tutored in: ";
    std::getline(std::cin, input);
    std::cout << "How many minutes was your session?: ";
    std::getline(std::cin, numInput);

    int hour = std::stoi(numInput) / 60;
    int min = std::stoi(numInput) % 60;

    file << getDate() << " : " << input << " - " << hour << " hour(s) and " << min << " minutes";
    file << std::endl;
}

void addNewSession(std::fstream &file, float &time){
    std::string input;
    std::cout << "Please enter what subject you tutored in: ";
    std::getline(std::cin, input);

    int hour = (int)time / 60;
    int min = (int)time % 60;

    file << getDate() << " : " << input << " - " << hour << " hour(s) and " << min << " minutes";
    file << std::endl;
}


void timeSession(std::fstream &file){
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    std::string input;

    start = std::chrono::system_clock::now(); //records begin time
    std::cout << "Press any key when you reach the end of your session" << std::endl;
    while (!std::cin.get()) { /*Just waits for end of session*/}
    end = std::chrono::system_clock::now(); //records end time

    std::chrono::duration<float> duration = end - start; //calculate duration
    float minutes = std::chrono::duration_cast<std::chrono::seconds>(duration).count() / 60;
    LOG(minutes);

    addNewSession(file, minutes); //adds to log file
}



#endif //TUTORLOGGING_HEADER_HPP
