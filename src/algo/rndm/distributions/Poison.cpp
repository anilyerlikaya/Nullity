#include "distributions.h"

nl::distributions::Poison::Poison(int mean) : mt(std::time(nullptr)), lambda(mean) {}

float nl::distributions::Poison::random_variable() {
    int k = 0;
    float p = 1, l = exp(-lambda);

    while (p > l) {
        k++;
        p *= (float)mt() / mt.max();
    }

    return (float)k;
} 

std::pair<nl::Matrix2d<float>, nl::Array<int>> nl::distributions::Poison::generate_data(int data_size, int feature_size, int class_count) {
    nl::Matrix2d<float> dataset(feature_size, data_size, 0.0);
    //nl::Array<int> labels(data_size, 0);

    float value;
    for(int i=0; i<data_size; i++) {
        for(int j=0; j<feature_size; j++) {
            value = random_variable();
            dataset.set_point(i, j, value);
        }
        //labels.set_point(i, mt() % class_count);
    }

    nl::Array<int> labels = nl::distributions::generate_labels(class_count, dataset);

    return std::make_pair(dataset, labels);
}