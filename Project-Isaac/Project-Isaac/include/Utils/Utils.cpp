#include "pch/pch.hpp"

bool BoolRand(const double probability) {
    //static std::random_device gen;
    static std::default_random_engine gen(SEED);
    std::bernoulli_distribution boolDitribution(probability);
    
    const auto temp = boolDitribution(gen);
    //std::clog << temp << std::endl;

    return temp;
}

int IntRand(int low, int high) {
    //static std::random_device gen;
    static std::default_random_engine gen(SEED);
    std::uniform_int_distribution<> intDitribution(low, high);

    const auto temp = intDitribution(gen);
    //std::clog << temp << std::endl;

    return temp;
}

double RealRand(double low, double high) {
    //static std::random_device gen;
    static std::default_random_engine gen(SEED);
    std::uniform_real_distribution<> realDitribution(low, high);

    const auto temp = realDitribution(gen);
    //std::clog << temp << std::endl;

    return temp;
}
