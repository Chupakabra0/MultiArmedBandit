#include "pch/pch.hpp"
#include "Bandit.hpp"

bool Bandit::GenerateReward() {
    std::random_device generator;
    std::bernoulli_distribution ditribution(this->probability_);

    const auto generatedValue = ditribution(generator);

    //std::clog << std::format("Generated value: {}\n", generatedValue);
    //std::clog << std::format("Probability value: {}%\n", this->probability_);

    return generatedValue;
}

double Bandit::GetProbability() {
    return this->probability_;
}

std::string Bandit::GetName() {
    return this->name_;
}
