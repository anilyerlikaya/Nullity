#include "test.h"

int test_features(int argc, char** argv) {
    printf("\n*******************\nTest: FeatureTests\n*******************\n\n");

    nl::Array<float> array1(4, 0.0f);
    nl::Array<float> array2(5, 2.0f);
    float dist = array1.find_dist(array2);
    printf("dist: %lf\n", dist);

    return 0;
}