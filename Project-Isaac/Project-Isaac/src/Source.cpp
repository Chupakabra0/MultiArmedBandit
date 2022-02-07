#include "pch/pch.hpp"

#include "BanditPool/BanditPool.hpp"

#include "BanditAlgorithms/EpsilonGreedy/EpsilonGreedy.hpp"
#include "BanditAlgorithms/EpsilonKGreedy/EpsilonKGreedy.hpp"
#include "BanditAlgorithms/Pursuit/Pursuit.hpp"
#include "BanditAlgorithms/UCB1/UCB1.hpp"
#include "BanditAlgorithms/BernoulliThompson/BernoulliThompson.hpp"
#include "BanditAlgorithms/Softmax/Softmax.hpp"

int main(const int argc, char* argv[]) {
    auto banditPool = std::make_shared<BanditPool>();

    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.15, "A")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.25, "B")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.30, "C")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.25, "D")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.05, "E")));

    auto algor = std::make_unique<Softmax>(banditPool, 15);

    const auto s = algor->Execute(10000);

    std::cout << std::format("Total reward: {}\n", s->GetTotalReward());
    std::cout << std::format("Total regret: {}\n\n", s->GetTotalRegret());

    for (auto j = 0; j < s->GetPoolSize(); ++j) {
        const auto bandit = s->GetPool()->GetBandit(j);

        std::cout << std::format("Arm \"{}\" ({})\n", bandit->GetName(), bandit->GetProbability());
        std::cout << std::format("Reward count: {}\n", s->GetRewardCount(j));
        std::cout << std::format("Reward rate: {}\n", s->GetRewardRate(j));
        std::cout << std::format("Choose count: {}\n", s->GetChooseCount(j));
        std::cout << std::format("Choose rate: {}\n", s->GetChooseRate(j));
        std::cout << std::format("------------------------\n");
    }
    std::cout << std::format("========================================\n");

    return EXIT_SUCCESS;
}
