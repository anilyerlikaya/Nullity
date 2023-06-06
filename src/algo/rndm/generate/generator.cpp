#include "generator.h"

nl::random::rndm_generator::rndm_generator(int min, int max) {
        std::random_device rd;
        engine.seed(rd());
        _min = min;
        _max = max;
        dist = std::uniform_int_distribution<int>(_min, _max);
    };

int nl::random::rndm_generator::rndm_int_value() {
        return dist(engine);
}