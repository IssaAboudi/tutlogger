#include "Files/files.hpp"
#include "header.hpp"

//======================================================
/*
 * Purpose of this program is to make logging tutoring hours
 * more convenient. When I tutor someone, I need to log the hours
 * I spend tutoring in a spreadsheet. Instead of always dealing
 * with the spreadsheet. This application would let me save it to a
 * text file which I can copy over to the spreadsheet after all my
 * sessions
 * ~ Matthew Issa Aboudi
 */
//======================================================


void unitTest(){
    student newStudent;
    newStudent.name = "Test1";
    newStudent.subject = "Subject1";
    student newStudent1;
    newStudent1.name = "Test2";
    newStudent1.subject = "Subject2";
    student newStudent2;
    newStudent2.name = "Test3";
    newStudent2.subject = "Subject3";

    std::vector<student> students;
    students.push_back(newStudent);
    students.push_back(newStudent1);
    students.push_back(newStudent2);

    std::string filePath = getFilePath();
    updateLog(filePath, students);
}

int main() {
//    //Create folder for our program to store data in (easily accessible by the user)
//    std::string folder = getFilePath(); //stores OS specific file path (see function definition)
//    if(createFolder(folder) == false) { //actually makes the directory (OS Specific)
//        std::cout << "Error code -999: Could not create Directory" << std::endl;
//        std::cin.get();
//        exit(999);
//    }
//    std::fstream tutoringFile; //to reference the text file
//    int menuInput; //userInput for the menu
//
//    std::string tutoringLog = folder;
//    tutoringLog += "/tutoringLog.txt"; //makes the text file
//
//    tutoringFile.open(tutoringLog, std::ios::in | std::fstream::app); //open the log file to add to
//    if(tutoringFile.fail()){ //if it fails to open - perhaps it doesn't exist -> create new file
//        std::cout << "File failed to open. Creating new file" << std::endl;
//        tutoringFile.open(tutoringLog, std::ios::out); //make the file
//        tutoringFile.open(tutoringLog, std::ios::in | std::fstream::app);
//    } //otherwise we're good
//
//    do {
//        std::cout << "Tutoring Logging Tool" << std::endl;
//        std::cout << "-=-=-=-=-=-=-=-=-=-=-" << std::endl;
//        LOG(getDateTime());
//        std::cout << "1) Add new session" << std::endl;
//        std::cout << "2) Time new session" << std::endl;
//        std::cout << "3) Exit" << std::endl;
//        std::cout << ">> ";
//        std::cin >> menuInput;
//        clearCIN(); //clear cin buffer
//
//        //TODO: make better keybindings. Maybe "esc" to exit, "a" to add and "v" to view?
//
//
//        switch(menuInput){
//            case 1:
//                addNewSession(tutoringFile);
//                break;
//            case 2:
//                timeSession(tutoringFile);
//                break;
//        }
//    } while(menuInput != 3);
//
//    tutoringFile << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl; //divide different program runs
//
//
//    tutoringFile.close();
//
//    SPACER();
//    LOG("Program Ending");
//    return 0;

    unitTest();
    return 0;
}

