#include <iostream>
#include <exception>

/* 
 * Exception List:
 * InitializationException: Cannot initialize a holder
 * ********************/
class InitializationException : public std::exception {
private:
    const char* _msg;

public:
    InitializationException(char* msg) : _msg(msg) {}

    virtual const char* what() const throw () {
        printf("in what\n");
        return _msg; 
    }
};