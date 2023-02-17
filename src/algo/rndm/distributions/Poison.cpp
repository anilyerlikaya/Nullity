#include "distributions.h"

nl::distributions::Poison::Poison(int mean) {
    srand(time(0));
    this->lambda = mean;
}



float nl::distributions::Poison::random_variable() {
    int k = 0;
    float p = 1, l = exp(-lambda);

    while (p > l) {
        k++;
        p *= (float)rand() / RAND_MAX;
    }

    return (float)k;
} 

std::pair<nl::Matrix2d<float>, nl::Array<int>> nl::distributions::Poison::generate_data(int data_size, int feature_size, int class_count) {
    nl::Matrix2d<float> dataset(feature_size, data_size, 0.0);
    nl::Array<int> labels(data_size, 0);

    float max = -1.0;
    for(int i=0; i<data_size; i++) {
        for(int j=0; j<feature_size; j++) {
            float value = random_variable();
            dataset.set_point(i, j, value);
            max = value > max ? value : max;
        }
        labels.set_point(i, rand() % class_count);
    }

    return std::make_pair(dataset / max, labels);
}