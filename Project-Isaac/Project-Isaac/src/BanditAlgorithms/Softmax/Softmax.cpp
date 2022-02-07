#include "pch/pch.hpp"
#include "Softmax.hpp"

std::shared_ptr<BanditStats> Softmax::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        auto totalExpSum = 0.0;

        for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
            totalExpSum += std::exp(this->stats_->GetRewardRate(j) / this->t_);
        }

        for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
            this->probabilities_[j] = std::exp(this->stats_->GetRewardRate(j) / this->t_) / totalExpSum;
        }

        auto optimalIndex = 0;
        // TODO: util
        for (auto j = 0; j < this->probabilities_.size(); ++j) {
            if (j != optimalIndex) {
                auto temp = BoolRand(this->probabilities_[j]);

                if (temp) {
                    optimalIndex = j;
                    break;
                }
            }
        }
        //

        const auto reward = this->stats_->GetReward(optimalIndex);
    }

    return this->stats_;
}
