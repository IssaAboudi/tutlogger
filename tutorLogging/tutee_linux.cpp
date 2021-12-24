// Linux - Developed on Ubuntu 20.04

#if defined __unix__
#include "tutee.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

std::string createFolder() {
    std::cerr << "On Linux" << std::endl;
    char * userName = getlogin();
    LOG(std::string(userName));

    std::string filePath = "/home/";
    filePath += userName;
    filePath += "/Documents/tutlogger";

//    std::string filePath = "/Documents";

    const char * fp = filePath.c_str();


    if(mkdir(fp, 0777) == -1){
        LOG("Couldn't create folder");
    } else {
        LOG("Created folder");
    }

    LOG(filePath);
    return filePath;
}

#endif