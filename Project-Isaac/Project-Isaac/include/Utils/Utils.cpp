#include "pch/pch.hpp"

bool BoolRand(const double probability) {
    std::random_device gen;
    std::bernoulli_distribution boolDitribution(probability);
    return boolDitribution(gen);
}

int IntRand(int low, int high) {
    std::random_device gen;
    std::uniform_int_distribution<> intDitribution(low, high);
    return intDitribution(gen);
}
