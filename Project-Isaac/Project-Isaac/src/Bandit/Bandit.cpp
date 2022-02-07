#include "pch/pch.hpp"
#include "Bandit.hpp"

bool Bandit::GenerateReward() {
    const auto generatedValue = BoolRand(this->probability_);

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
