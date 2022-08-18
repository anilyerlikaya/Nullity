#pragma once

// headers
#include "utils.h"
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#ifdef _DEBUG
#define _DATA
#endif

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
        
#ifdef _DATA
        std::cout<<"DEBUG: _Array memory constructed!\n";
#endif
    }; 

    ~Array() {
        free(_data);

#ifdef _DATA
        printf("DEBUG: _Array memory flushed!\n");
#endif
    };


    // helper functions
    int size() { return _size; };
};


template<class T>
class Matrix2d {
private:
    Array<T>* _matrix;
    int _width, _height;

public:
    Matrix2d() {}

    /* Read from opencv mat */
    Matrix2d(cv::Mat mat) {
        std::cout << "size: " << mat.size << std::endl;

        return;
    }

    ~Matrix2d() {
        free(_matrix);

        return;
    }

};
