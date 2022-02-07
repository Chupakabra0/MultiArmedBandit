#include "pch/pch.hpp"
#include "UCB1.hpp"

std::shared_ptr<BanditStats> UCB1::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        std::for_each(this->ucb_.begin(), this->ucb_.end(),
            [this, i = 0](auto& val) mutable {
            val = this->stats_->GetRewardRate(i) +
                std::sqrt(2.0 * std::log(this->stats_->GetPoolSize()) / this->stats_->GetChooseCount(i));
            ++i;
        }
        );

        const auto index = std::distance(this->ucb_.begin(), std::max_element(this->ucb_.begin(), this->ucb_.end()));
        const auto reward = this->stats_->GetReward(index);
    }

    return this->stats_;
}
