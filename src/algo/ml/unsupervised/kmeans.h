/*
 * kmeans.h
 * Unsupervised Algorithm Implemenation: k-Means
 */

#include "data/data.h"
#include "data/consts.h"
#include "algo/rndm/generate/generator.h"

namespace nl::ml {

//https://developer.ibm.com/articles/cc-unsupervised-learning-data-classification/
class KMeans {
private:
    int max_iteration = 100, k;
    nl::Matrix2d<float> centroids;
    bool iterate(nl::Matrix2d<float>& dataset, nl::Array<int>& labels);
protected:
public:
    KMeans(int k);
    void fit(nl::Matrix2d<float>& dataset);                                                              // fill centroids
    nl::Array<int> predict(nl::Matrix2d<float>& dataset);                                                // make preds
};


} // end of namespace