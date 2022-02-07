#pragma once

#include "BanditAlgorithms/Base/BaseBanditAlgorithm.hpp"

class EpsilonGreedy : public BaseBanditAlgorithm {
public:
    explicit EpsilonGreedy(const std::shared_ptr<BanditPool>& pool, const double epsilon)
        : BaseBanditAlgorithm(pool), epsilon_(epsilon) {

    }

    EpsilonGreedy(const EpsilonGreedy&) = default;

    EpsilonGreedy(EpsilonGreedy&&) noexcept = default;

    ~EpsilonGreedy() override = default;

    EpsilonGreedy& operator=(const EpsilonGreedy&) = default;

    EpsilonGreedy& operator=(EpsilonGreedy&&) noexcept = default;

    std::shared_ptr<BanditStats> Execute(int n = 1) override;

private:
    double epsilon_;

    void Explore();
    void Exploit();
};

