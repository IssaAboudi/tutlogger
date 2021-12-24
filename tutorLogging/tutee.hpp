//
// Created by ma422 on 12/21/2021.
//

#ifndef TUTORLOGGING_TUTEE_HPP
#define TUTORLOGGING_TUTEE_HPP

#include <iostream>
#include "DebugMode.hpp"

struct student {
private:
    std::string name;
    std::string subject;
    int numSessions;

};


//Function definition depends on operating systems.
//See:
// tutee_windows.cpp - for Windows
// tutee_linux.cpp - for Linux/Unix based OS's
// tutee_mac.cpp - for Mac OS X (all) //TODO: Add definition for Mac OS

std::string createFolder();


#endif //TUTORLOGGING_TUTEE_HPP
