#include <random>

namespace nl::random {

class rndm_generator {
private:
    std::mt19937 engine;
    std::uniform_int_distribution<int> dist;
    int _min = 1, _max = 100;

public:
    rndm_generator(int min=1, int max=100);
    int rndm_int_value();
};

} // end of namespace => nl::random