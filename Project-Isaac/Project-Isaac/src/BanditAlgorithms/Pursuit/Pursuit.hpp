#pragma once
#include "BanditAlgorithms/Base/BaseBanditAlgorithm.hpp"

class Pursuit : public BaseBanditAlgorithm {
public:
    explicit Pursuit(const std::shared_ptr<BanditPool>& pool, const double beta)
        : BaseBanditAlgorithm(pool),
          probabilities_(pool->GetSize(), 1.0 / static_cast<double>(pool->GetSize())) {
        if (beta > 1.0 || beta < 0.0) {
            this->beta_ = 1.0;
        }
        else {
            this->beta_ = beta;
        }
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

