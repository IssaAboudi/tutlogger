#include "files.hpp"
//Implementation for all platforms

Status updateRecords(const std::string &filePath, std::vector<Student> students) {
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

        //Store data in JSON format
        data["Subject"] = students[i].subject;
        data["#ofSessions"] = students[i].numSessions;
        data["Total Time"] = students[i].time;

        header[students[i].name] = data; //creates header to contain the data organized above
        studentArray.push_back(header);
    }

    newFile << std::setw(4) << studentArray;
    LOG("Updated Log File");
    newFile.close();

    if(students.size() < 1){
        return EMPTY;
    } else {
        return FILLED;
    }

}

Status loadRecords(const std::string &filePath, std::vector<Student> &students){
    //pull tutee data from disk to vector students
    std::string logFile = filePath;
    logFile += "/students.json"; //json file

    LOG("loadRecords: " << filePath);
    LOG("loadRecords: " << logFile);

    std::fstream newFile(logFile, std::ios::in);
    if(newFile.fail()){ //if file fails to open
        LOG("loadRecords: Error reading log file");
        newFile.open(logFile, std::ios::out); //make logFile
        if(newFile.fail()){ //check if it fails again
            LOG("loadRecords: Error creating log file");
            return EMPTY; //PROBLEM
        }
        newFile.close();
        newFile.open(logFile, std::ios::in);
    }
    nlohmann::json tempJSON = nlohmann::json::array(); //json array to store data from file
    newFile >> tempJSON;
    LOG("loadRecords: tempJSON.size(): " << tempJSON.size());
    if(tempJSON.size() > 0) {
        for (int i = 0; i < tempJSON.size(); i++) { //loop through each json element in the array
            for (auto &x: tempJSON.at(i).items()) { //iterate through each JSON element like a map
                Student newStudent;
                newStudent.name = x.key(); //extract the key
                LOG("loadRecords: " << newStudent.name);

                //Pulls data from JSON file by accessing each entry
                newStudent.subject = x.value()["Subject"];
                newStudent.numSessions = x.value()["#ofSessions"];
                newStudent.time = x.value()["Total Time"];
                //TODO: Pull other data (TO BE IMPLEMENTED)

                students.push_back(newStudent);
            }
        }
    }
    LOG("loadRecords: # of students " << students.size());

    if(students.size() < 1){
        LOG("loadRecords: ERROR: No tutees modified yet");
        return EMPTY; //If there is nothing in the file
    } else {
        return FILLED; //if there is stuff in the file
    }

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
