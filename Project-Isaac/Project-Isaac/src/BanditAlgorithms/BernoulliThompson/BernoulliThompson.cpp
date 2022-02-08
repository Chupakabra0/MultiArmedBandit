#include "pch/pch.hpp"
#include "BernoulliThompson.hpp"

std::shared_ptr<BanditStats> BernoulliThompson::Execute(int n) {
    for (auto i = 0; i < n; ++i) {
        std::vector<double> temp(this->values_.size(), 0.0);
        std::for_each(temp.begin(), temp.end(),
            [this, i = 0](auto& el) mutable {
                std::random_device gen;
                //std::gamma_distribution<> gdAlpha(this->values_[i].first, 1);
                //std::gamma_distribution<> gdBeta(this->values_[i].second, 1);
                //const auto [x, y] = std::make_pair(gdAlpha(gen), gdBeta(gen));
                std::_Beta_distribution b(this->values_[i].first, this->values_[i].second);

                el = b(gen);
                ++i;
            }
        );

        const auto index = std::distance(temp.begin(), std::max_element(temp.begin(), temp.end()));
        const auto reward = this->stats_->GetReward(index);

        this->values_[index].first  += static_cast<int>(reward);
        this->values_[index].second += 1 - static_cast<int>(reward);
    }

    return this->stats_;
}
