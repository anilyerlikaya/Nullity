#include "test.h"
#include <algo/rndm/distributions/distributions.h>

int test_rndm_generate(int argc, char** argv) {
    printf("\n*******************\nTest: Random Data Generate\n*******************\n\n");

    nl::distributions::Poison poison_dist(3);

    std::pair<nl::Matrix2d<float>, nl::Array<int>> dataset_pair = poison_dist.generate_data(10, 5, 2);
    nl::Matrix2d<float> dataset = dataset_pair.first;
    nl::Array<int> labels = dataset_pair.second;

    printf("dataset => rows: %d, cols: %d\nDataset:\n", dataset.height(), dataset.width());
    for(int i=0; i<dataset.height(); i++) {
        printf("%d. item: ", i);
        for(int j=0; j<dataset.width(); j++) {
            printf("%lf ", dataset.get_point(i, j));
        }
        printf(" => %d\n", labels.get_point(i));
    }
    
    return 0;
}