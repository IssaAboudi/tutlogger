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


void addTutee(const std::string &filePath, std::vector<Student> &students);

void unitTest(){
    //currently trying to develop using the JSON library
    // -- writing out to a file with updateRecords()
    // -- reading in a file with loadRecords()

    Student newStudent;
    newStudent.name = "Test1";
    newStudent.subject = "Subject1";
    Student newStudent1;
    newStudent1.name = "Test2";
    newStudent1.subject = "Subject2";
    Student newStudent2;
    newStudent2.name = "Test3";
    newStudent2.subject = "Subject3";

    std::vector<Student> students;
    students.push_back(newStudent);
    students.push_back(newStudent1);
    students.push_back(newStudent2);

    std::string filePath = getFilePath();
    updateRecords(filePath, students);

    std::vector<Student> readIn;
    loadRecords(filePath, readIn);
    listStudents(readIn);

}

int main() {
#if UNIT_TEST == OFF
    //Create folder for our program to store data in (easily accessible by the user)
    std::string folder = getFilePath(); //stores OS specific file path (see function definition)
    //TODO: fix this -> if we already have a folder it will trigger this error. We want to check that the folder isn't there, not that we didn't make one
    createFolder(folder);
//    if(createFolder(folder) == false) { //actually makes the directory (OS Specific)
//        std::cout << "Error code -999: Could not create Directory. Press enter to close" << std::endl;
//        std::cin.get();
//        exit(999);
//    }

    std::fstream tutoringFile; //to reference the text file
    int menuInput; //userInput for the menu
    std::vector<Student> tutees; //vector of students
    Student* student = nullptr; //specific Student we want to reference
    bool firstRun = false;

    loadRecords(folder, tutees); //read in Student data from JSON file
    makeLog(folder, tutoringFile); //opens the log file for editing - if it doesn't exists, creates it.

    do {
        if(tutees.size() < 1){
            std::cout << "Need to add a Tutee before proceeding" << std::endl;
            addTutee(folder, tutees);
        } else if(firstRun == false){
            listStudents(tutees);
            firstRun = true;
        }

        //menu for tutlogger application & selection //TODO: make this a function
        std::cout << "Tutoring Logging Tool" << std::endl;
        std::cout << "-=-=-=-=-=-=-=-=-=-=-" << std::endl;
        LOG(getDateTime());
        std::cout << "1) Add new session" << std::endl;
        std::cout << "2) Time new session" << std::endl;
        std::cout << "3) Add new Tutee" << std::endl;
        std::cout << "4) List all Tutees" << std::endl;
        std::cout << "5) Exit" << std::endl;
        std::cout << ">> ";
        std::cin >> menuInput;
        clearCIN(); //clear cin buffer


        switch(menuInput){
            case 1:
                student = selectTutee(tutees); //returns pointer to specific tutee we are working with in vector
                addNewSession(tutoringFile, student); //manually enter session details
                updateRecords(folder, tutees); //apply changes to the JSON file
                break;
            case 2:
                student = selectTutee(tutees); //returns pointer to specific tutee we are working with in vector
                timeSession(tutoringFile, student); //begins a timer
                updateRecords(folder, tutees); //apply changes to the JSON file
                break;
            case 3:
                addTutee(folder, tutees);
                break;
            case 4:
                listStudents(tutees); //displays students in vector
                break;
        }
    } while(menuInput != 5);

    //TODO: Separate entries by day rather than program runs
    tutoringFile << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl; //divide different program runs


    tutoringFile.close();

    SPACER();
    LOG("Program Ending");
#else
    unitTest();
#endif
    return 0;
}

