// Linux - Developed on Ubuntu 20.04

#if defined __unix__
#include "files.hpp"

//OS Specific
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

void updateLog(const std::string &filePath, std::vector<student> students) {
    std::string logFile = filePath;
    logFile += "/students.json";
    LOG(filePath);
    LOG(logFile);
    std::fstream newFile;
    newFile.open(logFile, std::ios::in | std::ios::out);
    if(newFile.fail()){ //if it fails to open - perhaps it doesn't exist -> create new file
        std::cout << "File failed to open. Creating new file" << std::endl;
        newFile.open(logFile, std::ios::out); //make the file
        newFile.open(logFile, std::ios::in);

    } //otherwise we're good

    nlohmann::json studentArray = nlohmann::json::array();
    for (int i = 0; i < students.size(); ++i) {
        nlohmann::json tempJSON;
        tempJSON["Name"] = students[i].name;
        tempJSON["Subject"] = students[i].subject;
        tempJSON["#ofSessions"] = students[i].numSessions;
        studentArray.push_back(tempJSON);
    }
    newFile << std::setw(4) << studentArray;
    LOG("Updated Log File");
    newFile.close();
}

std::string getFilePath(){
    LOG("On Linux");
#if RELEASE == ON
    char * userName = getlogin();
    LOG(std::string(userName));

    std::string filePath = "/home/";
    filePath += userName;
    filePath += "/Documents/tutlogger";
#else
   std::string filePath = "../Documents";
#endif

    return filePath;
}

bool createFolder(const std::string &filePath) {
    const char * fp = filePath.c_str();

    if(mkdir(fp, 0777) == -1){
        LOG("Couldn't create folder");
        return false;
    } else {
        LOG("Created folder");
        return true;
    }
}


#endif