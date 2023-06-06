#include "test.h"
#include <algo/rndm/distributions/distributions.h>

int test_rndm_generate(int argc, char** argv) {
    printf("\n*******************\nTest: Random Data Generate\n*******************\n\n");

    // parameters
    int class_size = 2;
    int mean = 5;
    int variance = 5;
    int dataset_size = 20;
    int feature_space = 5;

    nl::distributions::Poison poison_dist(mean);
    std::pair<nl::Matrix2d<float>, nl::Array<int>> dataset_pair = poison_dist.generate_data(dataset_size, feature_space, class_size);
    nl::Matrix2d<float> dataset = dataset_pair.first;
    nl::Array<int> labels = dataset_pair.second;

    printf("dataset => rows: %d, cols: %d\nPoison_Dataset:\n", dataset.height(), dataset.width());
    for(int i=0; i<dataset.height(); i++) {
        printf("%d. item: ", i);
        for(int j=0; j<dataset.width(); j++) {
            printf("%lf ", dataset.get_point(i, j));
        }
        printf(" => %d\n", labels.get_point(i));
    }

    printf("\n***********************************\n");

    nl::distributions::Gaussian gaussian_dist(mean, variance);
    dataset_pair = gaussian_dist.generate_data(dataset_size, feature_space, class_size);
    dataset = dataset_pair.first;
    labels = dataset_pair.second;

    printf("dataset => rows: %d, cols: %d\nGaussian_Dataset:\n", dataset.height(), dataset.width());
    for(int i=0; i<dataset.height(); i++) {
        printf("%d. item: ", i);
        for(int j=0; j<dataset.width(); j++) {
            printf("%lf ", dataset.get_point(i, j));
        }
        printf(" => %d\n", labels.get_point(i));
    }
    
    return 0;
}