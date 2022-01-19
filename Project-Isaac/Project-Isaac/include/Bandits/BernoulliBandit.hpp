#pragma once

#include "Bandits/IBandit.hpp"
#include "Rewards/BooleanReward.hpp"

class BernoulliBandit : public IBandit {
public:
    explicit BernoulliBandit() = default;

    explicit BernoulliBandit(const double probability) {
        if (probability < 0.0 || probability > 1.0) {
            this->probability_ = 1.0;
        }
        else {
            this->probability_ = probability;
        }
    }

    BernoulliBandit(const BernoulliBandit&) = default;

    BernoulliBandit(BernoulliBandit&&) noexcept = default;

    ~BernoulliBandit() noexcept = default;

    BernoulliBandit& operator=(const BernoulliBandit&) = default;

    BernoulliBandit& operator=(BernoulliBandit&&) noexcept = default;

    BooleanReward* GenerateReward() override;

    [[nodiscard]] double GetProbability();

private:
    double probability_{ 0.0 };
};
