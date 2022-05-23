#include "pch/pch.hpp"
#include "Pursuit.hpp"

std::shared_ptr<BanditStats> Pursuit::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        auto totalExpSum = 0.0;

        for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
            totalExpSum += this->stats_->GetRewardRate(j) == std::numeric_limits<double>::infinity() ?
                0.0 :
                std::exp(this->u_[j]);
        }

        for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
            this->probabilities_[j] = this->stats_->GetRewardRate(j) == std::numeric_limits<double>::infinity() ?
                1.0 :
                std::exp(this->u_[j]) / totalExpSum;
            this->u_[j] += this->stats_->GetRewardRate(j) == std::numeric_limits<double>::infinity() ?
                0.0 :
                this->beta_ * (this->stats_->GetRewardRate(j)
                    - static_cast<double>(this->stats_->GetTotalReward()) / this->stats_->GetTotalChoose());
        }

        std::vector<int> indexes(this->probabilities_.size(), 0);
        std::iota(indexes.begin(), indexes.end(), 0);

        const auto optimalIndex = Rand(indexes.begin(), indexes.end(), this->probabilities_.begin(), this->probabilities_.end());
        const auto reward = this->stats_->GetReward(optimalIndex);
    }

    return this->stats_;
}

//std::shared_ptr<BanditStats> Pursuit::Execute(int n) {
//    for (auto i = 0; i < n; ++i) {
//        auto optimalIndex = this->stats_->GetLocalOptimalBanditIndex();
//
//        for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
//            this->probabilities_[j] +=
//                j != optimalIndex ?
//                -this->beta_ * this->probabilities_[j] :
//                this->beta_ * (1.0 - this->probabilities_[j]);
//        }
//
//        std::vector<int> indexes(this->probabilities_.size(), 0);
//        std::iota(indexes.begin(), indexes.end(), 0);
//
//        optimalIndex = Rand(indexes.begin(), indexes.end(), this->probabilities_.begin(), this->probabilities_.end());
//
//        const auto reward = this->stats_->GetReward(optimalIndex);
//    }
//
//    return this->stats_;
//}
