// Linux - Developed on Ubuntu 20.04

#if defined __unix__
#include "files.hpp"

//OS Specific
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

std::string getFilePath(){
    LOG("getFilePath: " << "On Linux");
#if RELEASE == ON
    char * userName = getlogin();
    LOG(std::string(userName));

    std::string filePath = "/home/";
    filePath += userName;
    filePath += "/Documents/tutlogger";
#else
   std::string filePath = "./Documents";
#endif

    return filePath;
}

bool createFolder(const std::string &filePath) {
    const char * fp = filePath.c_str();

    bool isThere = false;

    if(mkdir(fp, 0777) != -1){ //if could create a folder, yay
        LOG("createFolder: Creating Folder");
        isThere = true; //yes we created a folder
    } else if(errno == EEXIST) { //if folder already there
        LOG("createFolder: Folder already exists");
        isThere = true;
    }else { //if couldn't create a folder
        LOG("createFolder: Unexpected Error Creating Folder");
        isThere = false;
    }

    return isThere;
}



#endif