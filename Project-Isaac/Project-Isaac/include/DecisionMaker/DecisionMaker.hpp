#pragma once

#include "BanditPools/BernoulliBanditPool.hpp"

class DecisionMaker {
public:
    explicit DecisionMaker(const std::shared_ptr<BernoulliBanditPool>& pool/*,*/
        /*const std::shared_ptr<IBanditChooseStrategy>& banditStrategy*/)
        : pool_(pool)/*, banditStrategy_(banditStrategy)*/ {

    }

    DecisionMaker(const DecisionMaker&) = default;

    DecisionMaker(DecisionMaker&&) noexcept = default;

    ~DecisionMaker() noexcept = default;

    DecisionMaker& operator=(const DecisionMaker&) = default;

    DecisionMaker& operator=(DecisionMaker&&) noexcept = default;

    [[nodiscard]] std::shared_ptr<BernoulliBanditPool> GetPool() const {
        return this->pool_;
    }

    void SetPool(const std::shared_ptr<BernoulliBanditPool>& pool) {
        this->pool_ = pool;
    }



private:
    std::shared_ptr<BernoulliBanditPool> pool_;
    //std::shared_ptr<IBanditChooseStrategy> banditStrategy_;
};
