#pragma once

#include "BanditStats/BanditStats.hpp"
#include "BanditPool/BanditPool.hpp"

class BaseBanditAlgorithm {
public:
    explicit BaseBanditAlgorithm(const std::shared_ptr<BanditPool>& pool)
        : stats_(std::make_shared<BanditStats>(pool)) {

    }

    BaseBanditAlgorithm(const BaseBanditAlgorithm&) = default;

    BaseBanditAlgorithm(BaseBanditAlgorithm&&) noexcept = default;

    virtual ~BaseBanditAlgorithm() = default;

    BaseBanditAlgorithm& operator=(const BaseBanditAlgorithm&) = default;

    BaseBanditAlgorithm& operator=(BaseBanditAlgorithm&&) noexcept = default;

    virtual std::shared_ptr<BanditStats> Execute(int n = 1) = 0;
    virtual std::shared_ptr<BanditStats> InitStat(int n = 1) {
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < this->stats_->GetPoolSize(); ++j) {
                this->stats_->GetReward(j);
            }
        }

        return this->stats_;
    }

    [[nodiscard]] const std::shared_ptr<BanditStats> GetStats() const {
        return this->stats_;
    }

protected:
    std::shared_ptr<BanditStats> stats_;
};

