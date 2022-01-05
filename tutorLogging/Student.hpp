//
// Created by issaaboudi on 1/1/22.
//

#ifndef TUTORLOGGING_STUDENT_HPP
#define TUTORLOGGING_STUDENT_HPP

#include <iostream>
#include "Ext/json.hpp"

//Student Data Structure association with files
struct Student {
public:
    std::string name = "";
    std::string subject = ""; //TODO: what if tutee comes for multiple subjects with tutor?
                              // - for now maybe ignore this?
    int numSessions = 0;
    int time = 0; //store total time with Student in minutes;
    //TODO: When getting total time with Student format in Hours & minutes
    //TODO: Come up with more fields that might be useful to store


    friend std::ostream& operator<<(std::ostream &fs, const Student &rval)  {
        fs << rval.name;
        return fs;
    }
};



#endif //TUTORLOGGING_STUDENT_HPP
