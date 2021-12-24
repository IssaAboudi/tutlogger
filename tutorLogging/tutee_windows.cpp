
//Windows 32 Bit and 64 Bit

#if defined _WIN32
#include "tutee.hpp"
#include <unistd.h>

std::string createFolder(){
    std::cerr << "On Windows" << std::endl;
    char * userName = getenv("username");
    LOG(std::string(userName));

    std::string filePath = "C:/Users/";
    filePath += userName;
    filePath += "/Documents/tutlogger";

    const char * fp = filePath.c_str();


    if(mkdir(fp) == -1){
        LOG("Couldn't create folder");
    } else {
        LOG("Created folder");
    }

    LOG(filePath);
    return filePath;
}

#endif

