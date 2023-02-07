#pragma once

#include <iostream>

#include <string>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>

bool fileExist(std::string path);                                                                           /* check if file exist */
bool dirExist(std::string path);                                                                            /* check if directory exist */
void createFile(std::string folder_path, std::string file_name);                                            /* create file */
std::ofstream createStream(std::string folder_path, std::string file_name);                                 /* create file and return it */
void createDir(std::string path);                                                                           /* create directory */

