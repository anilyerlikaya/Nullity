/*
 * Distributions.h
 * Initialize various probability distributions 
 * TODO:
 *      - generate a base_distribution class as parent
 *      - add others as needed
 */

#include "data/data.h"
#include "utils/maths.h"
#include "algo/ml/unsupervised/kmeans.h"

#include <random>
//#include <cstdlib> // for rand()

namespace nl::distributions {

nl::Array<int> generate_labels(int class_size, nl::Matrix2d<float>& dataset);                                         // static function for generating labels

class Bernoulli {
private:
    float min_prob = 0.0, max_prob = 1.0;
    float prob;
protected:
public:
    Bernoulli(float _prob);
    float expected_value();
    float variance();
    void change_prob(float _val);
    float get_prob();
};

class Uniform {
private:
    float min_prob = 0.0, max_prob = 1.0;
    float prob;
    int begin, end;

    void calculate_prob();
protected:
public:
    Uniform(int _begin, int _end);
    float expected_value();
    float variance();
    void change_begin(int _begin);
    void change_end(int _end);
    float get_prob();
};

class Poison {
private:
    int lambda;
    std::mt19937 mt;
    float random_variable();
protected:
public:
    Poison(int mean);
    std::pair<nl::Matrix2d<float>, nl::Array<int>> generate_data(int data_size, int feature_size, int class_count);
};

class Gaussian {                                                                                                            // Normal distribution
private:
    int mean, var;
    std::mt19937 mt;
    float random_variable();
protected:
public:
    Gaussian(int mean=0, int variance=1);
    std::pair<nl::Matrix2d<float>, nl::Array<int>> generate_data(int data_size, int feature_size, int class_count);
};


} // end of namespace