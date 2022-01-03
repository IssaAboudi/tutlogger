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
    //currently trying to develop using the JSON library
    // -- writing out to a file with updateRecords()
    // -- reading in a file with loadRecords()

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
    updateRecords(filePath, students);

    std::vector<student> readIn;
    loadRecords(filePath, readIn);

    listStudents(readIn);

}

int main() {
#if UNIT_TEST == OFF
    //Create folder for our program to store data in (easily accessible by the user)
    std::string folder = getFilePath(); //stores OS specific file path (see function definition)
    //TODO: fix this -> if we already have a folder it will trigger this error. We want to check that the folder isn't there, not that we didn't make one
//    if(createFolder(folder) == false) { //actually makes the directory (OS Specific)
//        std::cout << "Error code -999: Could not create Directory. Press enter to close" << std::endl;
//        std::cin.get();
//        exit(999);
//    }

    std::fstream tutoringFile; //to reference the text file
    int menuInput; //userInput for the menu
    std::vector<student> tutees;

    makeLog(folder, tutoringFile); //opens the log file for editing - if it doesn't exists, creates it.

    do {
        menuScreen(menuInput); //menu for tutlogger application & selection

        //TODO: let tutors add tutees to keep track of
        // - Tutors add new tutees, or select tutees they've already added
        // - - when they select a tutee, num of sessions will go up when they add hours
        // - - can view all sessions with that particular tutee

        switch(menuInput){
            case 1:
                //TODO: Select tutee to update information of
                // - might need to adjust addNewSession and timeSession functions
                // - to include a reference to the student object we're modifying
                addNewSession(tutoringFile);
                break;
            case 2:
                timeSession(tutoringFile);
                break;
        }
    } while(menuInput != 3);

    tutoringFile << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl; //divide different program runs


    tutoringFile.close();

    SPACER();
    LOG("Program Ending");
#else
    unitTest();
#endif
    return 0;
}

