#pragma once
#include "BanditAlgorithms/Base/BaseBanditAlgorithm.hpp"

class BernoulliThompson : public BaseBanditAlgorithm {
public:
    explicit BernoulliThompson(const std::shared_ptr<BanditPool>& pool)
        : BaseBanditAlgorithm(pool), values_(pool->GetSize(), { 1.0, 1.0 }) {

    }

    BernoulliThompson(const BernoulliThompson&) = default;

    BernoulliThompson(BernoulliThompson&&) noexcept = default;

    ~BernoulliThompson() override = default;

    BernoulliThompson& operator=(const BernoulliThompson&) = default;

    BernoulliThompson& operator=(BernoulliThompson&&) noexcept = default;

    std::shared_ptr<BanditStats> Execute(int n = 1) override;

private:
    std::vector<std::pair<double, double>> values_;
};

