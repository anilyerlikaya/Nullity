#pragma once

// headers
#include "utils.h"
#include <iostream>

//namespace nul {

/*
    - A basic container for keeping 1D data which is basically an array
    - Currently, it takes only numarical values
*/
template<class T>
class Array {
private:
    T* _data; 
    int _size;

protected:
    /****************************
    ************ ? **************
    ****************************/

public:
    /*  Default constructor  */
    Array() {};
    
    /*  Default allocated constructor  */
    Array(int _size, T _default_value=0) {
        _data = defloc(_size, _default_value);
        
        for(int i=0; i<_size; i++)
            printf("%d: %d\n", i, _data[i]);

        this->_size = _size;
        
        std::cout<<"DEBUG: _Array memory constructed!\n";
    }; 

    ~Array() {
        free(_data);

        printf("DEBUG: _Array memory flushed!\n");
    };


    // helper functions
    int size() { return _size; };
};

// }