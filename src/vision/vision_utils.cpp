#include "vision_utils.h"

/*
 * Plot opencv frame
 */
void showFrame(cv::Mat frame, std::string name, int delay) {
    cv::imshow(name, frame);
    cv::waitKey(delay);
    cv::destroyWindow(name);
}