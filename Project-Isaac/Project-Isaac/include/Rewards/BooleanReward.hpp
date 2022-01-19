#pragma once

#include "IReward.hpp"

class BooleanReward : public IReward {
public:
    explicit BooleanReward() = default;

    explicit BooleanReward(bool value) : value_(value) {

    }

    BooleanReward(const BooleanReward&) = default;
    
    BooleanReward(BooleanReward&&) noexcept = default;

    ~BooleanReward() noexcept = default;

    BooleanReward& operator=(const BooleanReward&) = default;

    BooleanReward& operator=(BooleanReward&&) noexcept = default;

    [[nodiscard]] bool GetValue() const {
        return this->value_;
    }

    void SetValue(const bool value) {
        this->value_ = value;
    }

private:
    bool value_{ false };
};
