#include "utils.h"

/*
 * Check if file at path exists or not
 */
bool fileExist(std::string path) {
    int res = access(path.c_str(), R_OK);
    printf("res: %d\n", res);
    
    if (res < 0){
        if(errno == ENOENT) 
            printf("file does not exist!\n");
        else if(errno == EACCES)
            printf("file exist but not readable\n");
        else
            printf("wtf\n");

        return false;
    }

    return true;
}

/*
 * Check if directory at path exists or not
 */
bool dirExist(std::string path) {
    DIR* dir = opendir(path.c_str());
    bool result = false;

    if (dir) {
        closedir(dir);
        result = true;
    } /*else if(errno == ENOENT)
        printf("directory does not exist\n");
    else if(errno == EACCES)
        printf("directory exists but not readable\n");
    else
        printf("wtf\n");*/

    return result;
}

/*
 * Create File
 */
void createFile(std::string folder_path, std::string file_name) {
    if(file_name.find(".") == std::string::npos)
        throw std::invalid_argument("Log file not have any extension!\n");
    
    if(!dirExist(folder_path))
        createDir(folder_path);
        
    std::ofstream outfile(folder_path + "/" + file_name);
    if(outfile.is_open())
        outfile.close();
    else
        throw std::runtime_error("Cannot create file!\n");
}

/*
 * Create File & Return it
 */
std::ofstream createStream(std::string folder_path, std::string file_name) {
    if(file_name.find(".") == std::string::npos)
        throw std::invalid_argument("Log file not have any extension!\n");
    
    if(!dirExist(folder_path))
        createDir(folder_path);
        
    std::ofstream outfile(folder_path + "/" + file_name, std::ofstream::out | std::ofstream::app); 
    if(!outfile.is_open())  
        throw std::runtime_error("Cannot create folder for outstream!\n");
    return outfile;
}

/*
 * Create Directory
 */
void createDir(std::string path) {
    if(!dirExist(path)) 
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}