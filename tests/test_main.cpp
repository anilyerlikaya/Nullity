#include "base/test.h"

int main(int argc, char** argv){
    printf("argc: %d\n", argc);
    
    if(argc > 1) {
        try {
            int test_id = std::stoi(argv[1]);
            printf("text selection: %d\n", test_id);
            /*
            * 1: video stream test (probably need improvements)
            * 2: matrix test
            * 3: point test - maybe kalman filter too?
            * 4: logger test
            * 5: ml algo tests
            * 6: random dataset generation test
            * inf => test params
            */

            int test_result = -1;
            switch(test_id) { 
                case 7:
                    throw std::invalid_argument("test_id: 10 not initialized yet!\n");
                    break;
                case 6:
                    test_result = test_rndm_generate(argc, argv);
                    break;
                case 5:
                    test_result = test_ml(argc, argv);
                    break;
                case 4:
                    test_result = test_logger(argc, argv);
                    break;
                case 3:
                    test_result = test_point(argc, argv);
                    break;
                case 2:
                    test_result = test_matrix(argc, argv);
                    break;
                case 1:
                    test_result = test_video(argc, argv);
                    break;
                case 0:
                default:
                    break;
            }
        } catch (const std::exception & e) {
            printf("Exception: %s\n", e.what());
        }
    }

    return 0;
}