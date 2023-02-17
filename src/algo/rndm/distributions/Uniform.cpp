#include "distributions.h"

nl::distributions::Uniform::Uniform(int _begin, int _end) {
if (!(_end > _begin))
        throw std::invalid_argument("In Uniform Distribution, end value must be larger than begin!\n");
    this->begin = _begin;
    this->end = _end;
    calculate_prob();
}

float nl::distributions::Uniform::expected_value() {
    return (begin + end) / 2.0;
}

float nl::distributions::Uniform::variance() {
    int dif = begin - end;
    return dif * dif / 12; 
}

void nl::distributions::Uniform::change_begin(int _begin) {
    if (!(this->end > _begin))
        throw std::invalid_argument("In Uniform Distribution, end value must be larger than begin!\n");
    this->begin = _begin;
    calculate_prob();
}

void nl::distributions::Uniform::change_end(int _end) {
    if (!(_end > this->begin))
        throw std::invalid_argument("In Uniform Distribution, end value must be larger than begin!\n");
    this->end = _end;
    calculate_prob();
}

float nl::distributions::Uniform::get_prob() {
    return prob;
}

void nl::distributions::Uniform::calculate_prob() {
    prob = 1.0 / (end - begin);
}