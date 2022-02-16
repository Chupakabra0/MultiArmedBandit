#pragma once

#include "BanditPool/BanditPool.hpp"
#include "BanditAlgorithms/Base/BaseBanditAlgorithm.hpp"

#include "BanditAlgorithms/EpsilonGreedy/EpsilonGreedy.hpp"
#include "BanditAlgorithms/EpsilonKGreedy/EpsilonKGreedy.hpp"
#include "BanditAlgorithms/Pursuit/Pursuit.hpp"
#include "BanditAlgorithms/UCB1/UCB1.hpp"
#include "BanditAlgorithms/BernoulliThompson/BernoulliThompson.hpp"
#include "BanditAlgorithms/Softmax/Softmax.hpp"

#include "sciplot/sciplot.hpp"

class BanditTest {
public:
    explicit BanditTest(const std::shared_ptr<BanditPool>& pool, const int n)
        : n_(n), pool_(pool) {

    }

    virtual ~BanditTest() = default;

    virtual void LaunchTest() = 0;

    [[nodiscard]] std::shared_ptr<BanditPool> GetPool() const {
        return this->pool_;
    }

    void SetPool(const std::shared_ptr<BanditPool>& pool) {
        this->pool_ = pool;
    }

    [[nodiscard]] int GetN() const {
        return this->n_;
    }

    void SetPool(const int n) {
        this->n_ = n;
    }

protected:
    int n_;
    std::shared_ptr<BanditPool> pool_;

    virtual void DrawPlots(const std::shared_ptr<sciplot::Plot>& regret,
        const std::shared_ptr<sciplot::Plot>& reward,
        const std::shared_ptr<sciplot::Plot>& convertion) {
        regret->show();
        reward->show();
        convertion->show();
    }
};
