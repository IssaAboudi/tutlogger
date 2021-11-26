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

//Quick Logging
#define DEBUG 1

#if DEBUG == 1
#define LOG(X) std::cout << X << std::endl
#define SPACER() std::cout << std::endl
#elif DEBUG == 0
#define LOG(X)
#define SPACER()
#endif

void clearCIN(void);


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
    int hour;
    int min;
    std::cout << "Please enter what subject you tutored in: ";
    std::getline(std::cin, input);
    std::cout << "How long was your session (hour.min): ";
    std::getline(std::cin, numInput);
    std::pair<std::string, std::string> time = breakTime(numInput, '.'); //TODO: decide whether delimiter is ':' or '.' (maybe both?)
    hour = std::stoi(time.first);
    min = std::stoi(time.second);


    file << getDate() << " : " << input << " " << hour << " hour(s) " << min << " mins";
    file << std::endl;
}

void clearCIN(void){
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}


#endif //TUTORLOGGING_HEADER_HPP
