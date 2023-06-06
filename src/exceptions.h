#pragma once

#include <iostream>
#include <exception>

/* 
 * Exception List:
 * InitializationException: Cannot initialize a holder
 */
class InitializationException : public std::exception {
private:
    std::string _msg;

public:
    InitializationException(std::string msg) : _msg(msg) {}

    const char* what() { 
        _msg = "Initialization Fault! " + _msg;
        return _msg.c_str(); 
    }
};


class PathNotFoundException : public std::exception {
private:
    std::string _msg;

public:
    PathNotFoundException(std::string msg) : _msg(msg) {}

    const char* what() {
        _msg = "PathNotFound! " + _msg;
        return _msg.c_str(); 
    }
};

static inline void print_warning(std::string msg) {
    printf("Warning! %s\n", msg.c_str());
}

