#include "distributions.h"

nl::distributions::Bernoulli::Bernoulli(float _prob) {
    if(!isBetween(_prob, min_prob, max_prob))
        throw std::invalid_argument("In Bernoulli Distribution, probability value must be between 0 and 1!\n");
    prob = _prob;
}

float nl::distributions::Bernoulli::expected_value() {
    return prob;
}

float nl::distributions::Bernoulli::variance(){
    return prob * (1 - prob);
}

void nl::distributions::Bernoulli::change_prob(float _val){
    prob = _val;
}

float nl::distributions::Bernoulli::get_prob() {
    return prob;
}