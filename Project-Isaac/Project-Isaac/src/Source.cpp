#include "pch/pch.hpp"

#include "BanditPool/BanditPool.hpp"

#include "BanditAlgorithms/EpsilonGreedy/EpsilonGreedy.hpp"
#include "BanditAlgorithms/EpsilonKGreedy/EpsilonKGreedy.hpp"
#include "BanditAlgorithms/Pursuit/Pursuit.hpp"
#include "BanditAlgorithms/UCB1/UCB1.hpp"
#include "BanditAlgorithms/BernoulliThompson/BernoulliThompson.hpp"
#include "BanditAlgorithms/Softmax/Softmax.hpp"

int main(const int argc, char* argv[]) {
    //std::vector<double> prob{ 0.1, 0.2, 0.2, 0.5, 0.0 };
    //std::vector<int> val{ 1, 3, 4, 8, 0 };

    //for (auto i = 0; i < 31; ++i) {
    //    std::cout << std::format("Rand {}: {}\n", i, Rand(val.begin(), val.end(), prob.begin(), prob.end()));
    //}

    auto banditPool = std::make_shared<BanditPool>();

    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.023, "Alex")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.03, "Boris")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.029, "Christofer")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.001, "Danny")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.05, "Edgar")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.06, "Fiona")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.0234, "Gregory")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.035, "Henry")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.01, "Inna")));
    banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.11, "Jane")));

    //banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.15, "A")));
    //banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.25, "B")));
    //banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.30, "C")));
    //banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.25, "D")));
    //banditPool->PushBandit(std::shared_ptr<Bandit>(new Bandit(0.05, "E")));

    //auto algor = std::make_unique<Softmax>(banditPool, 0.05);
    //auto algor = std::make_unique<UCB1>(banditPool);
    //auto algor = std::make_unique<BernoulliThompson>(banditPool);
    //auto algor = std::make_unique<Pursuit>(banditPool, 0.01);
    //auto algor = std::make_unique<EpsilonKGreedy>(banditPool, 0.05);
    auto algor = std::make_unique<EpsilonGreedy>(banditPool, 0.1);

    const auto s = algor->Execute(10'000);

    std::cout << std::format("Total atempts: {}\n", s->GetTotalChoose());
    std::cout << std::format("Total reward: {}\n", s->GetTotalReward());
    std::cout << std::format("Total regret: {}\n\n", s->GetTotalRegret());

    for (auto j = 0; j < s->GetPoolSize(); ++j) {
        const auto bandit = s->GetPool()->GetBandit(j);

        std::cout << std::format("Arm \"{}\" ({:.2f}%)\n", bandit->GetName(), bandit->GetProbability() * 100.0);
        std::cout << std::format("Reward count: {}\n", s->GetRewardCount(j));
        std::cout << std::format("Reward rate: {:.2f}%\n", s->GetRewardRate(j) * 100.0);
        std::cout << std::format("Choose count: {}\n", s->GetChooseCount(j));
        std::cout << std::format("Choose rate: {:.2f}%\n", s->GetChooseRate(j) * 100.0);
        std::cout << std::format("------------------------\n");
    }
    std::cout << std::format("========================================\n");

    return EXIT_SUCCESS;
}
