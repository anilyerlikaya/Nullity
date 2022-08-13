#include "video.h"


/* Get Single Frame if Reader initialized! */
cv::Mat VideoReader::getFrame(){
    if(!_init)
        throw std::invalid_argument("VideoRecorder not set!");
        
    cv::Mat frame;
    _finished = !_cap.read(frame);

    if(_finished) {
        _init = false;
        throw std::runtime_error("New frame is empty!");
    }

    return frame;
}


/* return if stream continious or not */
bool VideoReader::isFinished() {
    if(!_init || _finished)
        return true;
    return false;
}


/* set fps fpr video capture */
void VideoReader::setFPS(int fps){ 
    _cap.set(cv::CAP_PROP_FPS, 15); 
}