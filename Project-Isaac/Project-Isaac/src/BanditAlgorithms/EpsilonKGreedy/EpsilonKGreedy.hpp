#pragma once

#include "BanditAlgorithms/Base/BaseBanditAlgorithm.hpp"

class EpsilonKGreedy : public BaseBanditAlgorithm {
public:
    explicit EpsilonKGreedy(const std::shared_ptr<BanditPool>& pool, const double c)
        : BaseBanditAlgorithm(pool), c_(c), epsilon_(1.0) {

    }

    EpsilonKGreedy(const EpsilonKGreedy&) = default;

    EpsilonKGreedy(EpsilonKGreedy&&) noexcept = default;

    ~EpsilonKGreedy() override = default;

    EpsilonKGreedy& operator=(const EpsilonKGreedy&) = default;

    EpsilonKGreedy& operator=(EpsilonKGreedy&&) noexcept = default;

    std::shared_ptr<BanditStats> Execute(int n = 1) override;

private:
    double epsilon_;
    double c_;

    void Explore() const;
    void Exploit() const;
    [[nodiscard]] double GetD() const;
};

