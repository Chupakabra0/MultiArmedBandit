#include "pch/pch.hpp"
#include "Softmax.hpp"

std::shared_ptr<BanditStats> Softmax::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        auto totalExpSum = 0.0;

        for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
            totalExpSum += this->stats_->GetRewardRate(j) == std::numeric_limits<double>::infinity() ?
                0.0 :
                std::exp(this->stats_->GetRewardRate(j) / this->t_);
        }

        for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
            this->probabilities_[j] = this->stats_->GetRewardRate(j) == std::numeric_limits<double>::infinity() ?
                1.0 / this->stats_->GetPoolSize() :
                std::exp(this->stats_->GetRewardRate(j) / this->t_) / totalExpSum;
        }

        std::vector<int> indexes(this->probabilities_.size(), 0);
        std::iota(indexes.begin(), indexes.end(), 0);

        const auto optimalIndex = Rand(indexes.begin(), indexes.end(), this->probabilities_.begin(), this->probabilities_.end());
        const auto reward       = this->stats_->GetReward(optimalIndex);
    }

    return this->stats_;
}
