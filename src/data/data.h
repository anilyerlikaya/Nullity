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
 * A basic container for keeping 1D data which is basically an array
 * Currently, it takes only numarical values
*/
template<class T>
class Array {
private:
    T* _data; 
    int _size = -1;
    bool initialized = false;

protected:
    /****************************
    ************ ? **************
    ****************************/

public:
    /*  Default constructor  */
    Array() {}
    
    /* Constructor v1 */
    Array(int size, T _default_value=0) {
        this->_size = size;
        _data = defloc(_size, _default_value);

        initialized = true;
    }

    /* copy constructor */
    Array(const Array & arr) {        
        T* temp = new T[arr._size];
        std::copy(arr._data, arr._data + arr._size, temp);

        // delete old memory
        clear();

        this->size = arr._size;
        this->_data = temp;    

        initialized = true;    
    }

    /* Copy Assignment */
    Array& operator=(const Array& arr){
        if(this != &arr) {    // protect against invalid self-assingment
            T* temp = new T[arr._size];
            std::copy(arr._data, arr._data + arr._size, temp);

            // delete old memory
            clear();

            this->_size = arr._size;
            this->_data = temp;

            initialized = true;
        }

        return *this;
    }

    // initialize with a default memory
    void init(int size, T _value=0) {
        if(initialized)
            clear();

        _size = size;
        _data = defloc(_size, _value);

        initialized = true;
    }

    // initialize with coping data
    void row_init(int size, T* row){
        clear();

        // mem init and allocate
        T* temp = new T[size];
        std::copy(row, row + size, temp);

        _size = size;  
        _data = temp;

        initialized = true;
    }

    /*
     * Setters
     */


    /*
     * Getters
     */
    
    // get data at specific position
    T get_point(int index) { return _data[index]; }

    // get all memory
    T* get_array() { return _data; }

    // helper functions
    int size() { return _size; };

    void clear() {
        if(initialized)
            delete[] _data;
        initialized = false;
    }
    ~Array() { clear(); }
};


/*
 * Single Channel Imgs
 * Only keeps width and height
*/ 
template<class T>
class Matrix2d {
private:
    Array<T>* _matrix;
    int _width=-1, _height=-1;
    bool initialized = false;

public:
    /* Default Constructor */
    Matrix2d() {}

    /* Read from opencv mat */
    Matrix2d(cv::Mat mat) {
        // check if img has single channel
        if(mat.channels() > 1)
            throw std::invalid_argument("matrix2d can only initialize with opencv gray-scale imgs!\n");

        // other matrix informations
        _width = mat.cols;
        _height = mat.rows;

        // memory allocation and set
        _matrix = new Array<T>[_height];
        for(int i=0; i<_height; i++)
            _matrix[i].row_init(_width, mat.row(i).data);

        // for(int i=0; i<_height; i++){
        //     printf("row %d =>", i+1);
        //     for(int j=0; j<_width; j++) {
        //         std::cout << " " << static_cast<unsigned>(_matrix[i].get_point(j));
        //     }
        //     printf("\n");
        // } 

        initialized = true;
    }

    /* 
     * Read from Array<T>
     * Constructor v2
    */
    Matrix2d(int width, int height, Array<T>* array) {
        if(this->_width != -1 || this->_height != -1)
            delete [] this->_matrix;

        this->_width = width;
        this->_height = height;

        // memory allocation and set
        _matrix = new Array<T>[_height];
        for(int i=0; i<_height; i++)
            _matrix[i].row_init(_width, array[i].get_array());

        initialized = true;
    }

    // copy constructor
    Matrix2d(const Matrix2d & other) {
        // allocate new memory
        Array<T>* temp = new Array<T>[other._height];
        for(int i=0; i<other._height; i++)
            temp[i].row_init(other._width, other._matrix[i].get_array());

        // delete old memory
        clear();

        // assignment
        this->_height = other._height;
        this->_width = other._width;
        this->_matrix = temp;

        initialized = true;
    }

    /* Copy Assignment */
    Matrix2d& operator=(const Matrix2d& other) {
        if(this != &other) {    // protect against invalid self-assingment
            // allocate new memory
            Array<T>* temp = new Array<T>[other._height];
            for(int i=0; i<other._height; i++)
                temp[i].row_init(other._width, other._matrix[i].get_array());

            // delete old memory
            clear();

            this->_height = other._height;
            this->_width = other._width;
            this->_matrix = temp;

            initialized = true;
        }

        return *this;
    }


    /*
     * Getters
     */
    int get_width() { return this->_width; }  
    int get_height() { return this->_height; }  
    T* get_row(int index) { 
        if(index < _height)
            return this->_matrix[index].get_array(); 
        return nullptr;        
    }
    
    /* get single point
     * y: row
     * x: column
     */
    T get_point(int y, int x) {
        if(x < _width && y < _height)
            return _matrix[y].get_point(x);
        return -1;
    }

    /* get whole matrix */
    Array<T>* get_matrix() { return this->_matrix; } 

    /* get opencv mat */
    cv::Mat get_opencv_mat() {
        cv::Mat img = cv::Mat(_height, _width, CV_8UC1);

        for(int i = 0; i < _height; i++) 
            for(int j=0; j < _width; j++)
                img.at<T>(i,j) = get_point(i,j);

        return img;
    }

    void clear() {
        if(initialized)
            delete[] _matrix;
        
        this->_width = -1;
        this->_height = -1;
        initialized = false;
    }
    ~Matrix2d() { clear(); }
};


/*
 * Img with multi channels
 * Keeps also channels
*/ 
template<class T>
class Matrix3d {
private:
    Array<T>** _matrix;
    int _width=-1, _height=-1, _channels=-1;
    bool initialized = false;

public:
    /* Default Constructor */
    Matrix3d() {}

    /* 
     * Read from opencv mat 
     * Constructor v1
     */
    Matrix3d(cv::Mat mat) {
        // other matrix informations
        _width = mat.cols;
        _height = mat.rows;
        _channels = mat.channels();

        // split channels
        std::vector<cv::Mat> channels(_channels);
        cv::split(mat, channels);

        // memory allocation and set
        _matrix = new Array<T>*[_channels];
        for(int i=0; i<_channels; i++) {
            _matrix[i] = new Array<T>[_height];
            for(int j=0; j<_height; j++)
                _matrix[i][j].row_init(_width, channels[i].row(j).data);
        }

        // for(int i=0; i<_channels; i++){
        //     printf("channel: %d\n", i+1);
        //     for(int j=0; j<_height; j++) {
        //         printf("%d. row =>", j);
        //         for(int t=0; t<_width; t++) 
        //             std::cout << " " << static_cast<unsigned>(_matrix[i][j].get_point(t));
        //     }
        //     printf("\n");
        // } 

        initialized = true;
    }

    // copy constructor
    Matrix3d(const Matrix3d & other) {
        // allocate memory
        Array<T>** temp = new Array<T>*[other._channels];
        for(int i=0; i<other._channels; i++) {
            temp[i] = new Array<T>[other._height];
            for(int j=0; j<other._height; j++)
                temp[i][j].
                row_init(other._width, other._matrix[i][j].get_array());
        }

        // delete old memory
        clear();

        // assignment
        this->_height = other._height;
        this->_width = other._width;
        this->_channels = other._channels;
        this->_matrix = temp;

        initialized = true;
    }

    /* Copy Assignment */
    Matrix3d& operator=(const Matrix3d & other) {
        if(this != &other) {    // protect against invalid self-assingment
            // allocate new memory
            Array<T>** temp = new Array<T>*[other._channels];
            for(int i=0; i<other._channels; i++) {
                temp[i] = new Array<T>[other._height];
                for(int j=0; j<other._height; j++)
                    temp[i][j].row_init(other._width, other._matrix[i][j].get_array());
            }

            // delete old memory
            clear();

            // assignment
            this->_height = other._height;
            this->_width = other._width;
            this->_channels = other._channels;
            this->_matrix = temp;

            initialized = true;
        }

        return *this;
    }

    /*
     * Getters
     */
    int get_width() { return this->_width; }  
    int get_height() { return this->_height; }  
    int get_channels() { return this->_channels; }

    /*
     * Return specific channel 
     * For BGR, 0: B, 1: G, 2: R 
     */
    Matrix2d<T> get_matrix2d(int channel) {
        if(channel >= this->_channels)
            throw std::invalid_argument("Requested channel not initialized!\n");

        return Matrix2d<T>(_width, _height, this->_matrix[channel]);
    }

    /* 
     * Get opencv mat
     * Be careful about data type
     */
    cv::Mat get_opencv_mat() {
        if(_channels == 1)  // if single channel
            return get_matrix2d(1).get_opencv_mat();
        else if(_channels == 3){ // 3 channels: BGR
            cv::Mat img = cv::Mat(_height, _width, CV_8UC3);
            
            //option 1: 
            // std::vector<cv::Mat> channels;
            // cv::split(img, channels);
            // for(int c = 0; c < _channels; c++)
            //     for(int i = 0; i < _height; i++) 
            //         for(int j=0; j < _width; j++)
            //            channels[c].at<T>(i,j) = _matrix[c][i].get_point(j);
            // cv::merge(channels, img);

            //option 2:
            for(int c = 0; c < _channels; c++)
                for(int i = 0; i < _height; i++) 
                    for(int j=0; j < _width; j++)
                       img.at<cv::Vec3b>(i,j)[c] = _matrix[c][i].get_point(j);

            return img;   
        } else 
            throw std::runtime_error("Currently only single and 3 channels can be processed into opencv mat!\n");

        return cv::Mat();
    }


    /*
     * Memory 
     */
    void clear() {
        if(initialized) {
            for(int i=0; i<_channels; i++)
                delete[] _matrix[i];
            delete[] this->_matrix;
        } 

        this->_channels = -1;
        this->_width = -1;
        this->_height = -1;

        initialized = false;
    }

    ~Matrix3d() { clear(); }
};


/*
 * Point2d: (x,y)
 * Types can be short, int, float, ...
 */
template<class T>
class Point2d {

public:
    T x, y;

    /* Default Constructor */
    Point2d() {}

    /* Constructor v1 */
    Point2d(T _x, T _y) {
        this->x = _x;
        this->y = _y;
    }

    /* Copy Constructor */
    Point2d(const Point2d & other) {
        this->x = other.x;
        this->y = other.y;
    }

    /* Copy Assignment */
    Point2d operator=(const Point2d & other) {
        this->x = other.x;
        this->y = other.y;
    }


    /*
     * Getters
     */

    
    
    ~Point2d() {}
};