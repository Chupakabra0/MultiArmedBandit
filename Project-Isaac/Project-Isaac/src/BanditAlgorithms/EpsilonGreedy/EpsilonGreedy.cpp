#include "pch/pch.hpp"
#include "EpsilonGreedy.hpp"

std::shared_ptr<BanditStats> EpsilonGreedy::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        auto isEpsilon = BoolRand(this->epsilon_);

        if (isEpsilon) {
            this->Explore();
        }
        else {
            this->Exploit();
        }
    }

    return this->stats_;
}

void EpsilonGreedy::Explore() {
    const auto index  = IntRand(0, this->stats_->GetPoolSize() - 1);
    const auto reward = this->stats_->GetReward(index);
}

void EpsilonGreedy::Exploit() {
    auto optimalBanditIndex = this->stats_->GetLocalOptimalBanditIndex();
    std::vector<int> optimalBanditIndexes;

    for (auto i = 0; i < this->stats_->GetPoolSize(); ++i) {
        if (this->stats_->GetRewardRate(i) >= this->stats_->GetRewardRate(optimalBanditIndex)) {
            optimalBanditIndexes.push_back(i);
        }
    }

    const auto temp = IntRand(0, optimalBanditIndexes.size() - 1);
    const auto reward = this->stats_->GetReward(optimalBanditIndexes[temp]);
}
