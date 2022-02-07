#pragma once

#include <vector>
#include <memory>

#include "Bandit/Bandit.hpp"

class BanditPool {
public:
    explicit BanditPool() = default;

    explicit BanditPool(const std::shared_ptr<Bandit>& bandit) : bandits_(1, bandit) {

    }

    explicit BanditPool(const std::vector<std::shared_ptr<Bandit>>& bandits)
        : bandits_(bandits) {

    }

    BanditPool(const BanditPool&) = default;

    BanditPool(BanditPool&&) noexcept = default;

    ~BanditPool() noexcept = default;

    BanditPool& operator=(const BanditPool&) = default;

    BanditPool& operator=(BanditPool&&) noexcept = default;

    [[nodiscard]] size_t GetSize() const {
        return this->bandits_.size();
    }

    [[nodiscard]] std::shared_ptr<Bandit> GetBandit(const size_t index) const {
        return this->bandits_.at(index);
    }

    void PushBandit(std::shared_ptr<Bandit> bandit) {
        this->bandits_.push_back(bandit);
    }

    [[nodiscard]] bool GetReward(const size_t index) {
        return this->bandits_.at(index)->GenerateReward();
    }

private:
    std::vector<std::shared_ptr<Bandit>> bandits_{};

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
