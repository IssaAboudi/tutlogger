// Linux - Developed on Ubuntu 20.04

#if defined __unix__
#include "files.hpp"

//OS Specific
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

std::string getFilePath(){
    LOG("getFilePath: " << "On Linux");
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
        LOG("createFolder:" << "Couldn't create folder");
        return false;
    } else {
        LOG("createFolder:" << "Created folder");
        return true;
    }
}


#endif