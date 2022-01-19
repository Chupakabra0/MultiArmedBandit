#pragma once

#include "Rewards/IReward.hpp"

struct IBandit {
public:
    virtual IReward* GenerateReward() = 0;
};
