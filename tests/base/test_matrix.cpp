#include "test.h"

int test_matrix(int argc, char** argv) {
    printf("\n*******************\nTest: Custom Matrix\n*******************\n\n");

    try {
        std::string test_image(argv[2]);
        printf("test_image: %s\n", test_image.c_str());

        cv::Mat frame = cv::imread(test_image);        
        
        Matrix3d<uchar> matrix(frame);
        printf("matrix => w: %d, h: %d, c: %d\n", matrix.get_width(), matrix.get_height(), matrix.get_channels());
        Matrix3d<uchar> temp = matrix;

        Matrix2d<uchar> blue = temp.get_matrix2d(0);
        Matrix2d<uchar> temp_blue = blue;
        showFrame(temp_blue.get_opencv_mat(), "temp_blue");

        temp = matrix;
        showFrame(temp.get_opencv_mat(), "RGB");

        Matrix2d<uchar> error = matrix.get_matrix2d(4);
    } catch (const std::exception & e) {
        printf("Exception: %s\n", e.what());
        return -100;
    }

    return 0;
}