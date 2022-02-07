#include "pch/pch.hpp"

bool BoolRand(const double probability) {
    static std::random_device gen;
    //static std::default_random_engine gen;
    std::bernoulli_distribution boolDitribution(probability);
    
    const auto temp = boolDitribution(gen);
    //std::clog << temp << std::endl;

    return temp;
}

int IntRand(int low, int high) {
    static std::random_device gen;
    //static std::default_random_engine gen;
    std::uniform_int_distribution<> intDitribution(low, high);

    const auto temp = intDitribution(gen);
    //std::clog << temp << std::endl;

    return temp;
}
