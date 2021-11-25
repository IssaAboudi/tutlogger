//
// Created by ma422 on 11/25/2021.
//

#ifndef TUTORLOGGING_HEADER_HPP
#define TUTORLOGGING_HEADER_HPP

#define DEBUG 1

#if DEBUG == 1
#define LOG(X) std::cout << X << std::endl
#elif DEBUG == 0
#define LOG(X)
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

void addNewSession(std::fstream &file){
    std::string input;
    std::cout << "Please enter what subject you tutored in: ";
    std::getline(std::cin, input);
    file << getDate() << " : " << input;
    file << std::endl;
}

void clearCIN(void){
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}


#endif //TUTORLOGGING_HEADER_HPP
