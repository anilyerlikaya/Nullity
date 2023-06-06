#pragma once

// headers
#include "helper.h"
#include "exceptions.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#ifdef _DEBUG
#define _DATA
#endif

namespace nl {

/*
 * Notes: all templates types must be numerical such as int, float or double
 */

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
    Array(int size=1, T _default_value=0) {                                                                     /*  Default constructor  */
        init(size, _default_value);
    }

    Array(const Array & arr) {                                                                                  /* copy constructor */
        T* temp = new T[arr._size];
        std::copy(arr._data, arr._data + arr._size, temp);

        // delete old memory
        clear();

        this->_size = arr._size;
        this->_data = temp;    

        initialized = true;    
    }

    Array& operator=(const Array& arr){                                                                         /* Copy Assignment */
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

    /*
     * Initializations
     */
    void init(int size, T _value=0) {                                                                           // initialize with a default memory
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
     * Getters & Setters
     */
    
    // get data at specific position
    T get_point(int index) { 
        if(index >= _size)
            throw std::invalid_argument("Cannot access not initialized data in an Array!");
        return _data[index]; 
    }

    // set data at specific poisiton
    void set_point(int index, T value) {
        if(index >= _size)
            throw std::invalid_argument("Cannot access not initialized data in an Array!");
        _data[index] = value;
    }

    // get all memory
    T* get_array() { return _data; }


    /*
     * Operations
     */
    Array& operator/(T val){                                                                                        // division to single value
        std::transform(_data, _data+_size, _data, [val](T x) {return x / val;});
        return *this;
    }

    Array& operator+(const Array& arr){                                                                              // Array sum with another array
        if(this->_size != arr._size)     
            throw std::runtime_error("Cannot get sum of two arrays that have unequal size!\n");
            
        for(int i=0; i<_size; i++) 
            _data[i] += arr._data[i];

        return *this;
    }

    float find_dist(Array<T>& arr, int dist_type=0) {                                                               // finde distance between two arrays => l2 norm for now (dist_type=0)
        if(_size != arr.size()) {
            print_warning("Only can find dist between same size arrays!");
            return -1.0;
        }
        
        float dist = .0;
        for(int i=0; i<_size; i++)
            dist += pow(get_point(i) - arr.get_point(i), 2);
        return sqrt(dist);
    }

    /*
     * Utility Functions
     */ 
    int size() { return _size; };

    /*
     * Others
     */
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
    Matrix2d(int width = 1, int height = 1, T default_value = 0) {
        _width = width;
        _height = height;

        // memory allocation and set
        _matrix = new Array<T>[_height];
        for(int i=0; i < _height; i++) 
            _matrix[i].init(_width, default_value);

        initialized = true;
    }

    /* Read from opencv mat */
    Matrix2d(cv::Mat mat) {
        clear();

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
        clear();

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
     * Getters & Setters
     */    
    T* get_row(int index) {                                                                                     // Get row array as type pointer!
        if(index < _height)
            return this->_matrix[index].get_array(); 
        return nullptr;        
    }

    Array<T>& get_row_array(int index) {
        if(index > _height)
            throw std::invalid_argument("Try to reach uninitialized memory in Matrix2d!\n");
        return this->_matrix[index]; 
    }

    void set_row(int index, Array<T> array){
        if(index > _height)
            throw std::invalid_argument("Try to reach uninitialized memory in Matrix2d!\n");
        else if(_width != array.size())
            throw std::invalid_argument("Invalid data size for data overwriting!\n");
        this->_matrix[index].row_init(_width, array.get_array());
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

    // set value in given position
    void set_point(int y, int x, T value) {
        if(!(x < _width && y < _height))
            throw std::invalid_argument("Invalid range to access memory in Matrix2d!\n");
        _matrix[y].set_point(x, value);
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

    /*
     * Operations
     */
    Matrix2d& operator/(T val){                                                                                 // division to single value
        //for(int i=0; i<_height; i++) 
            //_matrix[i] = _matrix[i] / val;
        std::transform(_matrix, _matrix+_height, _matrix, [val](Array<T> x) {return x / val;});
        return *this;
    } 

    /*
     * Utility Functions
     */
    int width() { return this->_width; }  
    int height() { return this->_height; }  

    /*
     * Others
     */
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
    
    ~Point2d() {}
};

/*
 * Rectange2d: (x1,y1,x2,y2)
 * Types can be short, int, float, ...
 */
template<class T>
class Rectangle2d {
private:
    // --------------------------------

protected:
    // --------------------------------

public:
    // top-left and bottom-right points of rectangle 
    Point2d<T> tl, br;

    // default constructor
    Rectangle2d() {}

    // Constructor v1
    // top-left = (x1, y1)
    // bottom-right = (x2, y2) 
    Rectangle2d(T x1, T y1, T x2, T y2) {
        tl = Point2d<T>(x1, y1);
        br = Point2d<T>(x2, y2);
    }

    // Constructor v1
    Rectangle2d(nl::Point2d<T> _tl, nl::Point2d<T> _br) {
        this->tl = _tl;
        this->br = _br;
    }

    ~Rectangle2d() {};
};

}                                                                                               // end of namespace "nl"