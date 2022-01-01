//
// Created by issaaboudi on 1/1/22.
//

#ifndef TUTORLOGGING_STUDENT_HPP
#define TUTORLOGGING_STUDENT_HPP

#include <iostream>
#include "Ext/json.hpp"

//Student Data Structure association with files
struct student {
public:
    std::string name = "";
    std::string subject = "";
    int numSessions = 0;


    friend std::ostream& operator<<(std::ostream &fs, const student &rval)  {
        fs << rval.name << " " << rval.subject << " " << rval.numSessions;
        return fs;
    }
};



#endif //TUTORLOGGING_STUDENT_HPP
