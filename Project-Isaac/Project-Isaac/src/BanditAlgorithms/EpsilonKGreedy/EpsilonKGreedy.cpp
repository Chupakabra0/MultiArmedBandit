#include "pch/pch.hpp"
#include "EpsilonKGreedy.hpp"

#include <algorithm>

std::shared_ptr<BanditStats> EpsilonKGreedy::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        const auto d = this->GetD();
        this->epsilon_ = d > 0 ? std::min(1.0, this->c_ * this->stats_->GetPoolSize() / (this->stats_->GetTotalChoose() + 1) / std::pow(d, 2.0)) : 1.0;

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

double EpsilonKGreedy::GetD() {
    std::vector<double> temp(this->stats_->GetPoolSize(), 0.0);
    for (auto i = 0; i < temp.size(); ++i) {
        temp[i] = this->stats_->GetRewardRate(i);
    }
    
    auto maxIter = std::max_element(temp.begin(), temp.end());
    const auto max = *maxIter;
    temp.erase(maxIter);

    const auto preMax = *std::max_element(temp.begin(), temp.end());
    const auto diff   = max - preMax;

    return diff;
}

void EpsilonKGreedy::Explore() {
    const auto index = IntRand(0, this->stats_->GetPoolSize() - 1);
    const auto reward = this->stats_->GetReward(index);
}

void EpsilonKGreedy::Exploit() {
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
