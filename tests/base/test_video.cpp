#include "test.h"

int test_video(int argc, char** argv) {
    printf("\n*******************\nTest: VideoStream\n*******************\n\n");

    std::string video_path(argv[2]);
    printf("video_path: %s\n", video_path.c_str());

    try {
        if(!fileExist(video_path))
            throw PathNotFoundException("Video File (" + video_path + ") not found!");
        
        VideoReader video_reader(video_path);

        while(!video_reader.isFinished()){
            cv::Mat frame = video_reader.getFrame();

            cv::imshow("frame", frame);
            cv::waitKey(33);
        }

        cv::destroyAllWindows();
    } catch (std::exception e) {
        printf("%s\n", e.what());   
    }

    return 0;
}