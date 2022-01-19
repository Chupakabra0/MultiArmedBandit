#include "pch/pch.hpp"

#include "BernoulliBandit.hpp"

BooleanReward* BernoulliBandit::GenerateReward() {
    std::random_device generator;
    std::bernoulli_distribution ditribution(this->probability_);

    const auto generatedValue = ditribution(generator);

    //std::clog << std::format("Generated value: {}\n", generatedValue);
    //std::clog << std::format("Probability value: {}%\n", this->probability_);

    return new BooleanReward(generatedValue);
}

double BernoulliBandit::GetProbability() {
    return this->probability_;
}
