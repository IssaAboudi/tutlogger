
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



int main() {

    std::fstream tutoringFile; //to reference the text file
    int menuInput; //userInput for the menu

    //need to figure out how to use chrono to get timestamp

    tutoringFile.open("tutoringLog.txt", std::ios::in | std::fstream::app); //open the log file to add to
    if(tutoringFile.fail()){ //if it fails to open - perhaps it doesn't exist -> create new file
        std::cout << "File failed to open. Creating new file" << std::endl;
        tutoringFile.open("tutoringLog.txt", std::ios::out); //make the file
        tutoringFile.open("tutoringLog.txt", std::ios::in | std::fstream::app);
    } //otherwise we're good

    do {
        std::cout << "Tutoring Logging Tool" << std::endl;
        std::cout << "-=-=-=-=-=-=-=-=-=-=-" << std::endl;
        LOG(getDateTime());
        std::cout << "1) Add new session" << std::endl;
        std::cout << "2) View sessions" << std::endl;
        std::cout << "3) Exit" << std::endl;
        std::cout << ">> ";
        std::cin >> menuInput;
        clearCIN(); //clear cin buffer

        //TODO: make better keybindings. Maybe "esc" to exit, "a" to add and "v" to view?


        switch(menuInput){
            case 1:
                addNewSession(tutoringFile);
                break;
            case 2:
                //TODO: List contents of file in neat format - make new function
                break;
        }
    } while(menuInput != 3);



    tutoringFile.close();

    SPACER();
    LOG("Program Ending");
    return 0;
}

