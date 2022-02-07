#pragma once
#include "BanditAlgorithms/Base/BaseBanditAlgorithm.hpp"

class Softmax : public BaseBanditAlgorithm {
public:
    explicit Softmax(const std::shared_ptr<BanditPool>& pool, const double t)
        : BaseBanditAlgorithm(pool), t_(t <= 0.0 ? std::numeric_limits<double>::epsilon() : t),
        probabilities_(pool->GetSize(), 1.0 / static_cast<double>(pool->GetSize())) {

    }

    Softmax(const Softmax&) = default;

    Softmax(Softmax&&) noexcept = default;

    ~Softmax() override = default;

    Softmax& operator=(const Softmax&) = default;

    Softmax& operator=(Softmax&&) noexcept = default;

    std::shared_ptr<BanditStats> Execute(int n = 1) override;

private:
    double t_;
    std::vector<double> probabilities_;
};
