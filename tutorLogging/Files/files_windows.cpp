
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
    bool isThere = false;

    if(mkdir(fp) != -1){
        LOG("createFolder: Creating Folder");
        isThere = true; //yes we created a folder
    } else if(eerno == EEXIST){
        LOG("createFolder: Folder already exists");
        isThere = true;
    } else {
        LOG("createFolder: Unexpected Error Creating Folder");
        isThere = false;
    }

}

#endif

