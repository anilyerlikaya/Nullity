#include "Logger.h"

nl::Logger* nl::Logger::logger = nullptr;

nl::Logger::Logger(std::string file_name, std::string path): _path(path), _file_name(file_name) {
    stream = createStream(_path, _file_name); 

    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    stream << "CREATED AT " + s + "\n------------------------------------------\n\n";
    stream.flush();
}

nl::Logger::~Logger() {
    stream.close();
}
 
nl::Logger* nl::Logger::getInstance(const std::string fileName, const std::string path) {
    if(logger == nullptr) 
        logger = new nl::Logger(fileName, path);

    return logger;
}

void nl::Logger::Log(const std::string& message, nl::LogType type) {
    if(logger == nullptr)
        return;

    stream << getLogMessage(type) + message;
    stream.flush();
}

std::string nl::Logger::getLogPath() {
    if(logger != nullptr)
        return _path + "/" + _file_name;
    return "";
}