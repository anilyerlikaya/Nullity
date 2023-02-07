#pragma once

#include <fstream>
#include <chrono>

#include "utils.h"

namespace nl {

enum LogType {
    LOG_NOTYPE = -1,
    LOG_INFO = 0,
    LOG_WARNING = 1,
    LOG_ERROR = 2
};

class Logger {
private:
    /*Default Constructor - Private for single instance creation (singleton)*/
    Logger(std::string file_name, std::string folder_path);
    
    static Logger* logger;
    std::string _path, _file_name;
    std::ofstream stream;

    std::string getLogMessage(const LogType type) {
        if(type == LogType::LOG_WARNING)
            return "[WARNING] ";
        else if(type == LogType::LOG_ERROR)
            return "[ERROR] ";
        else if(type == LogType::LOG_NOTYPE)
            return "";
        return "[INFO] ";
    }
public:
    /* not cloneable */
    Logger(Logger const&) = delete;

    /* not assignable */
    void operator=(Logger const&) = delete;

    ~Logger();

    static Logger* getInstance(const std::string file_name = "logger.txt", const std::string folder_path = "./Logger");

    void Log(const std::string& message, LogType type = LogType::LOG_INFO);

    /*
        Getters
    */
    std::string getLogPath();    
};

}
