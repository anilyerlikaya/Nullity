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
