#include <iostream>
#include "src/data/data.h"

#include "src/vision/video.h"

#include <unistd.h>

int main(int argc, char** argv){
    Array<int> array(5, 3);

    printf("Lets GOOO...\n");
    
    if(argc == 1)
        return 0;

    try {
        std::string path(argv[1]);
        
        // check if file exist
        /*int res = access(path.c_str(), R_OK);
        printf("res: %d\n", res);
        if (res < 0){
            if(errno == ENOENT) 
                printf("file does not exist!\n");
            else if(errno == EACCES)
                printf("file exist but not readable\n");
            else
                printf("wtf\n");
        }*/

        VideoReader video_reader(path);
        //VideoReader video_reader(0);

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