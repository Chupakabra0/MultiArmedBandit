#pragma once
#include "BanditAlgorithms/Base/BaseBanditAlgorithm.hpp"

class Pursuit : public BaseBanditAlgorithm {
public:
    explicit Pursuit(const std::shared_ptr<BanditPool>& pool, const double beta)
        : BaseBanditAlgorithm(pool), beta_(beta > 1.0 || beta < 0.0 ? 1.0 : beta),
          probabilities_(pool->GetSize(), 1.0 / static_cast<double>(pool->GetSize())) {

    }

    Pursuit(const Pursuit&) = default;

    Pursuit(Pursuit&&) noexcept = default;

    ~Pursuit() override = default;

    Pursuit& operator=(const Pursuit&) = default;

    Pursuit& operator=(Pursuit&&) noexcept = default;

    std::shared_ptr<BanditStats> Execute(int n = 1) override;

private:
    double beta_;
    std::vector<double> probabilities_;
};

