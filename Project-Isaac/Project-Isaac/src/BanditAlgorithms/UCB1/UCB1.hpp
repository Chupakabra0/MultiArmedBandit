#pragma once
#include "BanditAlgorithms/Base/BaseBanditAlgorithm.hpp"

class UCB1 : public BaseBanditAlgorithm {
public:
    explicit UCB1(const std::shared_ptr<BanditPool>& pool)
        : BaseBanditAlgorithm(pool), ucb_(pool->GetSize(), 0.0) {

    }

    UCB1(const UCB1&) = default;

    UCB1(UCB1&&) noexcept = default;

    ~UCB1() override = default;

    UCB1& operator=(const UCB1&) = default;

    UCB1& operator=(UCB1&&) noexcept = default;

    std::shared_ptr<BanditStats> Execute(int n = 1) override;

private:
    std::vector<double> ucb_;
};

