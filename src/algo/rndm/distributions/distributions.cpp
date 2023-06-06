#include "distributions.h"

nl::Array<int> nl::distributions::generate_labels(int class_size, nl::Matrix2d<float> & dataset) {
    nl::ml::KMeans kmeans(class_size);
    kmeans.fit(dataset);
    nl::Array<int> labels = kmeans.predict(dataset);
    return labels;
}             