#include "pch/pch.hpp"

//#include "Bandits/BernoulliBandit.hpp"
#include "DecisionMaker/DecisionMaker.hpp"

int main(const int argc, char* argv[]) {
    //auto bandit = std::make_unique<BernoulliBandit>(0.5);

    //for (auto i = 0u; i < 10u; ++i) {
    //    auto temp = std::unique_ptr<BooleanReward>(bandit->GenerateReward());

    //    std::cout << std::format("{}. ", i + 1);
    //    temp->GetValue() ? std::cout << "SUCCESS!\n" : std::cout << "FAIL(\n";
    //}

    auto banditPool = std::make_unique<BernoulliBanditPool>();

    banditPool->PushBandit(std::shared_ptr<BernoulliBandit>(new BernoulliBandit(0.1)));
    banditPool->PushBandit(std::shared_ptr<BernoulliBandit>(new BernoulliBandit(0.2)));
    banditPool->PushBandit(std::shared_ptr<BernoulliBandit>(new BernoulliBandit(0.3)));
    banditPool->PushBandit(std::shared_ptr<BernoulliBandit>(new BernoulliBandit(0.4)));
    banditPool->PushBandit(std::shared_ptr<BernoulliBandit>(new BernoulliBandit(0.1)));

    for (auto i = 0u; i < 10u; i++) {
        std::cout << std::format("SIMULATION #{}:\n", i + 1);

        auto j = 0;
        for (auto bandit : *banditPool) {
            const auto reward = bandit->GenerateReward();
            std::cout << std::format("BANDIT #{} ({}%): {}\n",
                j + 1, bandit->GetProbability() * 100.0, reward->GetValue());

            ++j;
        }

        std::cout << std::string(30u, '-') << std::endl;
    }

    return EXIT_SUCCESS;
}
