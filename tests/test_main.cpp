#include "base/test.h"

int main(int argc, char** argv){
    printf("argc: %d\n", argc);
    
    if(argc > 1) {
        try {
            int test_id = std::stoi(argv[1]);
            printf("text selection: %d\n", test_id);
            /*
            * 2: video stream test (probably need improvements)
            * 3: matrix test
            * inf => test params
            */

            int test_result = -1;
            switch(test_id) { 
                case 3:
                    test_result = test_matrix(argc, argv);
                    break;
                case 2:
                    test_result = test_video(argc, argv);
                    break;
                case 1:
                default:
                    break;
            }
        } catch (std::exception e) {
            printf("Exception: %s\n", e.what());
        }
    }

    return 0;
}