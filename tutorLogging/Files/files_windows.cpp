
//Windows 32 Bit and 64 Bit

#if defined _WIN32
#include "files.hpp"

//OS Specific
#include <unistd.h>

std::string getFilePath(){
    LOG("On Windows");
    char * userName = getenv("username");
    LOG(std::string(userName));
#if RELEASE == ON
    std::string filePath = "C:/Users/";
    filePath += userName;
    filePath += "/Documents/tutlogger";
#else
    std::string filePath = "/Documents";
#endif
    return filePath;
}

bool createFolder(const std::string &filePath){
    const char * fp = filePath.c_str();

    if(mkdir(fp) == -1){
        LOG("Couldn't create folder");
        return false;
    } else {
        LOG("Created folder");
        return true;
    }

}

#endif

