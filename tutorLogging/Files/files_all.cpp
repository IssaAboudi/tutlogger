#include "files.hpp"
//Implementation for all platforms

//TODO: fix function
// - should return true if there are students in vector
// - return false if vector is empty
void updateRecords(const std::string &filePath, std::vector<student> students) {
    //store tutee information locally on disk
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

    nlohmann::json studentArray = nlohmann::json::array(); //make json array to store data to file
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

//TODO: fix function
// - should return true if there are students in the file to pull from
// - return false if empty
void loadRecords(const std::string &filePath, std::vector<student> &students){
    //pull tutee data from disk to vector students
    std::string logFile = filePath;
    logFile += "/students.json";

    LOG("loadRecords: " << filePath);
    LOG("loadRecords: " << logFile);

    std::fstream newFile(logFile, std::ios::in);
    if(newFile.fail()){
        std::cout << "Error reading log file" << std::endl;
        exit(-999);
    }
    nlohmann::json tempJSON = nlohmann::json::array(); //json array to store data from file
    newFile >> tempJSON;
    for(int i = 0; i < tempJSON.size(); i++) { //loop through each json element in the array
        for(auto &x : tempJSON.at(i).items()){ //iterate through each JSON element
            student newStudent;
            newStudent.name = x.key(); //extract the key
            LOG("loadRecords: " << newStudent.name);
            newStudent.subject = x.value()["Subject"];
            newStudent.numSessions = x.value()["#ofSessions"];
            students.push_back(newStudent);
        }
    }
    LOG(students.size());
}

void makeLog(const std::string &filePath, std::fstream &inputFile){
    std::string logFile = filePath;
    logFile += "/tutoringLog.txt";

    inputFile.open(logFile, std::ios::in | std::fstream::app); //open the log file to add to
    if(inputFile.fail()){ //if it fails to open - perhaps it doesn't exist -> create new file
        std::cout << "File failed to open. Creating new file" << std::endl;
        inputFile.open(logFile, std::ios::out); //make the file
        inputFile.open(logFile, std::ios::in | std::fstream::app);
    }
}
