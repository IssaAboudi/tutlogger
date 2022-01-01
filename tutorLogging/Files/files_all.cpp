#include "files.hpp"
//Implementation for all platforms

void updateRecords(const std::string &filePath, std::vector<student> students) {
    std::string logFile = filePath;
    logFile += "/students.json";
    LOG("updateRecords: " << filePath);
    LOG("updateRecords: " << logFile);
    std::fstream newFile;
    newFile.open(logFile,std::ios::out);
    if (newFile.fail()) { //if it fails to open - perhaps it doesn't exist -> create new file
        std::cout << "File failed to open. Creating new file" << std::endl;
        newFile.open(logFile, std::ios::out); //make the file
    } //otherwise we're good

    nlohmann::json studentArray = nlohmann::json::array();
    for (int i = 0; i < students.size(); ++i) {
        nlohmann::json data;
        nlohmann::json header;

        data["Subject"] = students[i].subject;
        data["#ofSessions"] = students[i].numSessions;
        header[students[i].name] = data;
        studentArray.push_back(header);
    }

    newFile << std::setw(4) << studentArray;
    LOG("Updated Log File");
    newFile.close();
}

void loadRecords(const std::string &filePath, std::vector<student> &students){
    std::string logFile = filePath;
    logFile += "/students.json";
    LOG("loadRecords: " << filePath);
    LOG("loadRecords: " << logFile);

    std::fstream newFile(logFile, std::ios::in);
    if(newFile.fail()){
        std::cout << "Error reading log file" << std::endl;
        exit(-999);
    }
    nlohmann::json tempJSON = nlohmann::json::array();
    newFile >> tempJSON;
    for(int i = 0; i < tempJSON.size(); i++) {
        for(auto &x : tempJSON.at(i).items()){
            student newStudent;
            newStudent.name = x.key();
            LOG("loadRecords: " << newStudent.name);
            newStudent.subject = x.value()["Subject"];
            newStudent.numSessions = x.value()["#ofSessions"];
            students.push_back(newStudent);
        }
    }
}
