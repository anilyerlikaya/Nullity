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
        printf("in what\n");
        return _msg.c_str(); 
    }
};


class PathNotFoundException : public std::exception {
private:
    std::string _msg;

public:
    PathNotFoundException(std::string msg) : _msg(msg) {}

    const char* what() {
        printf("in what\n");
        return _msg.c_str(); 
    }
};

