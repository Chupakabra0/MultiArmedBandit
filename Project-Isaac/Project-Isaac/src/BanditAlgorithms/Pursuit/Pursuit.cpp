#include "pch/pch.hpp"
#include "Pursuit.hpp"

std::shared_ptr<BanditStats> Pursuit::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        auto optimalIndex = this->stats_->GetLocalOptimalBanditIndex();

        for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
            this->probabilities_[j] +=
                j != optimalIndex ?
                -this->beta_ * this->probabilities_[j] :
                this->beta_ * (1.0 - this->probabilities_[j]);
        }

        for (auto j = 0; j < this->probabilities_.size(); ++j) {
            if (j != optimalIndex) {
                auto temp = BoolRand(this->probabilities_[j]);

                if (temp) {
                    optimalIndex = j;
                    break;
                }
            }
        }

        const auto reward = this->stats_->GetReward(optimalIndex);
    }

    return this->stats_;
}
