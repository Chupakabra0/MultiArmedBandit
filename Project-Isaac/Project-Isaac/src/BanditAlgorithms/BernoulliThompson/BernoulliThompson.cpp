#include "pch/pch.hpp"
#include "BernoulliThompson.hpp"

std::shared_ptr<BanditStats> BernoulliThompson::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        const auto index = std::distance(this->values_.begin(), std::max_element(this->values_.begin(), this->values_.end(),
            [](const auto& firstAlphaBeta, const auto& secondAlphaBeta) {
                const auto first  = std::beta(firstAlphaBeta.first, firstAlphaBeta.second);
                const auto second = std::beta(secondAlphaBeta.first, secondAlphaBeta.second);

                return first < second;
            }
        ));

        const auto reward = this->stats_->GetReward(index);

        this->values_[index].first  += static_cast<int>(reward);
        this->values_[index].second += 1 - static_cast<int>(reward);
    }

    return this->stats_;
}
