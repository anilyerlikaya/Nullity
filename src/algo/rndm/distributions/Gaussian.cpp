#include "distributions.h"

nl::distributions::Gaussian::Gaussian(int mean, int variance) : mt(std::time(nullptr)), mean(mean), var(variance) {}


/*
 * Normal random numbers generator - Marsaglia algorithm.
 */
float nl::distributions::Gaussian::random_variable() {                  
    float x, y, rsq;
    do {
        x = 2.0 * mt() / (float)mt.max() - 1.0;
        y = 2.0 * mt() / (float)mt.max() - 1.0;
        rsq = x * x + y * y;
    } while(rsq >= 1.0 || rsq == 0.);

    return x * sqrt(-2.0 * log(rsq) / rsq);
} 

std::pair<nl::Matrix2d<float>, nl::Array<int>> nl::distributions::Gaussian::generate_data(int data_size, int feature_size, int class_count) {
    nl::Matrix2d<float> dataset(feature_size, data_size, 0.0);
    //nl::Array<int> labels(data_size, 0);

    float value;
    for(int i=0; i<data_size; i++) {
        for(int j=0; j<feature_size; j++) {
            value = var * random_variable() + mean;
            dataset.set_point(i, j, value);
        }
        //labels.set_point(i, mt() % class_count);
    }

    nl::Array<int> labels = nl::distributions::generate_labels(class_count, dataset);

    return std::make_pair(dataset, labels);
}