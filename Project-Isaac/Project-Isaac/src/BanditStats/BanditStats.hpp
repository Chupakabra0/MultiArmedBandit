#pragma once

#include <numeric>

#include "Bandit/Bandit.hpp"
#include "BanditPool/BanditPool.hpp"

class BanditStats {
public:
    BanditStats(const std::shared_ptr<BanditPool>& pool)
        : pool_(pool), regret_(0.0), poolData_(pool->GetSize(), { 0.0, 0.0 }) {

    }

    BanditStats(const BanditStats&) = default;

    BanditStats(BanditStats&&) noexcept = default;

    ~BanditStats() = default;

    [[nodiscard]] std::shared_ptr<BanditPool> GetPool() const {
        return this->pool_;
    }

    void SetPool(const std::shared_ptr<BanditPool>&pool) {
        this->pool_ = pool;
    }

    [[nodiscard]] int GetTrueOptimalBanditIndex() {
        return std::distance(this->pool_->begin(), std::max_element(this->pool_->begin(), this->pool_->end(),
            [](std::shared_ptr<Bandit> a, std::shared_ptr<Bandit> b) {
                return a->GetProbability() < b->GetProbability();
            }
        ));
    }

    [[nodiscard]] int GetLocalOptimalBanditIndex() {
        std::vector<double> poolRewardRate(this->pool_->GetSize(), 0.0);
        std::for_each(poolRewardRate.begin(), poolRewardRate.end(),
            [i = 0, this](auto& a) mutable {
                a = this->GetRewardRate(i++);
            }
        );

        return std::distance(poolRewardRate.begin(), std::max_element(poolRewardRate.begin(), poolRewardRate.end()));
    }

    // TODO: REWORK
    [[nodiscard]] int GetTotalReward() const {
        return std::reduce(this->poolData_.begin(), this->poolData_.end(), std::pair<int, int>{ 0, 0 },
            [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                return std::pair<int, int>{ a.first + b.first, 0 };
            }
        ).first;
    }

    [[nodiscard]] double GetRewardRate(int index) const {
        return this->poolData_[index].second == 0 ? std::numeric_limits<double>::infinity() : static_cast<double>(this->poolData_[index].first) / static_cast<double>(this->poolData_[index].second);
    }
    [[nodiscard]] int GetRewardCount(int index) const {
        return this->poolData_[index].first;
    }

    // TODO: REWORK
    [[nodiscard]] int GetTotalChoose() const {
        return std::reduce(this->poolData_.begin(), this->poolData_.end(), std::pair<int, int>{ 0, 0 },
            [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                return std::pair<int, int>{ 0, a.second + b.second };
            }
        ).second;
    }

    [[nodiscard]] double GetChooseRate(int index) const {
        return this->poolData_[index].second == 0 ? std::numeric_limits<double>::infinity() : static_cast<double>(this->poolData_[index].second) / static_cast<double>(this->GetTotalChoose());
    }

    [[nodiscard]] double GetChooseCount(int index) const {
        return this->poolData_[index].second;
    }

    [[nodiscard]] double GetTotalRegret() const {
        return this->regret_;
    }

    void UpdateRegret(std::shared_ptr<Bandit> bandit) {
        this->regret_ += this->pool_->GetBandit(this->GetTrueOptimalBanditIndex())->GetProbability() - bandit->GetProbability();
    }

    [[nodiscard]] int GetPoolSize() {
        return this->pool_->GetSize();
    }

    bool GetReward(int index) {
        const auto reward = this->pool_->GetReward(index);

        this->UpdateRegret(this->pool_->GetBandit(index));

        this->poolData_.at(index).first += static_cast<int>(reward);
        ++this->poolData_.at(index).second;

        return reward;
    }

private:
    double regret_;

    std::shared_ptr<BanditPool> pool_;
    std::vector<std::pair<int, int>> poolData_;
};
