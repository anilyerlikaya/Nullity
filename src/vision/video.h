#pragma once

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#include <exceptions.h>

// need a parent class => Reader
class VideoReader{
private:
    bool _init = false, _finished = true;
    cv::VideoCapture _cap;
    
protected:
    /****************************
    ******** We'll See **********
    ****************************/

public:
    VideoReader(std::string source, int fps=15) {
        _cap.open(source, cv::CAP_FFMPEG);

        //if(!_cap.isOpened()) 
        //    throw(InitializationException("Cannot start stream from the source!"));

        _init = true;
        _finished = false;
    }

    VideoReader(int source) {
        _cap.open(source);

        if(!_cap.isOpened()) 
            throw(InitializationException("Cannot start stream from the source!"));

        _init = true;
        _finished = false;
    }

    // class member function declerations
    cv::Mat getFrame();
    bool isFinished();

    void setFPS(int fps);
};