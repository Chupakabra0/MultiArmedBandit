#pragma once

#include <vector>
#include <memory>

#include "Bandits/BernoulliBandit.hpp"

class BernoulliBanditPool {
public:
    explicit BernoulliBanditPool() = default;

    explicit BernoulliBanditPool(const std::shared_ptr<BernoulliBandit>& bandit) : bandits_(1, bandit) {

    }

    explicit BernoulliBanditPool(const std::vector<std::shared_ptr<BernoulliBandit>>& bandits)
        : bandits_(bandits) {

    }

    BernoulliBanditPool(const BernoulliBanditPool&) = default;

    BernoulliBanditPool(BernoulliBanditPool&&) noexcept = default;

    ~BernoulliBanditPool() noexcept = default;

    BernoulliBanditPool& operator=(const BernoulliBanditPool&) = default;

    BernoulliBanditPool& operator=(BernoulliBanditPool&&) noexcept = default;

    [[nodiscard]] size_t GetSize() const {
        return this->bandits_.size();
    }

    [[nodiscard]] std::shared_ptr<BernoulliBandit> GetBandit(const size_t index) const {
        return this->bandits_.at(index);
    }

    void PushBandit(std::shared_ptr<BernoulliBandit> bandit) {
        this->bandits_.push_back(bandit);
    }

    [[nodiscard]] std::shared_ptr<BooleanReward> GetReward(const size_t index) {
        return std::shared_ptr<BooleanReward>(this->bandits_.at(index)->GenerateReward());
    }

private:
    std::vector<std::shared_ptr<BernoulliBandit>> bandits_{};

public:
    auto begin() -> typename decltype(this->bandits_)::iterator {
        return this->bandits_.begin();
    }

    auto end() -> typename decltype(this->bandits_)::iterator {
        return this->bandits_.end();
    }

    auto cbegin() const -> typename decltype(this->bandits_)::const_iterator const {
        return this->bandits_.cbegin();
    }

    auto cend() const -> typename decltype(this->bandits_)::const_iterator const {
        return this->bandits_.cend();
    }

    auto rbegin() -> typename decltype(this->bandits_)::reverse_iterator {
        return this->bandits_.rbegin();
    }

    auto rend() -> typename decltype(this->bandits_)::reverse_iterator {
        return this->bandits_.rend();
    }

    auto crbegin() -> typename decltype(this->bandits_)::const_reverse_iterator const {
        return this->bandits_.crbegin();
    }

    auto crend() -> typename decltype(this->bandits_)::const_reverse_iterator const {
        return this->bandits_.crend();
    }
};
