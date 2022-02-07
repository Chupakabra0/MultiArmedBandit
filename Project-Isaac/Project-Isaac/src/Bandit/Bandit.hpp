#pragma once

#include <string>

class Bandit {
public:
    explicit Bandit() = delete;

    explicit Bandit(const double probability, const std::string& name) : name_(name) {
        if (probability < 0.0 || probability > 1.0) {
            this->probability_ = 1.0;
        }
        else {
            this->probability_ = probability;
        }
    }

    Bandit(const Bandit&) = default;

    Bandit(Bandit&&) noexcept = default;

    ~Bandit() noexcept = default;

    Bandit& operator=(const Bandit&) = default;

    Bandit& operator=(Bandit&&) noexcept = default;

    bool GenerateReward();

    [[nodiscard]] double GetProbability();

    [[nodiscard]] std::string GetName();

private:
    double probability_{ 0.0 };
    std::string name_;
};
