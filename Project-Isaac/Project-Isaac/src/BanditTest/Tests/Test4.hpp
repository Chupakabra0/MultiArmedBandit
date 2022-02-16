#pragma once

#include "BanditTest/Base/BanditTest.hpp"

#include <iostream>
#include <format>

class Test4 : public BanditTest {
public:
    explicit Test4(int n)
        : BanditTest(std::make_shared<BanditPool>(std::initializer_list{
                std::shared_ptr<Bandit>(new Bandit(0.40, "Alexia")),
                std::shared_ptr<Bandit>(new Bandit(0.40, "Bennett")),
                std::shared_ptr<Bandit>(new Bandit(0.25, "Charlez")),
                std::shared_ptr<Bandit>(new Bandit(0.30, "Don")),
                std::shared_ptr<Bandit>(new Bandit(0.15, "Emma")),
            }
            ), n) {

    }

    void LaunchTest() override {
        auto algorithms = std::vector<std::pair<std::shared_ptr<BaseBanditAlgorithm>, std::string>>{
            std::pair{std::make_shared<EpsilonKGreedy>(this->pool_, 0.05), "e-greedy(0.05)"},
            std::pair{std::make_shared<Pursuit>(this->pool_, 0.01), "pursuit(0.01)"},
            std::pair{std::make_shared<Softmax>(this->pool_, 0.02), "softmax(0.02)"},
            std::pair{std::make_shared<UCB1>(this->pool_), "ucb1"},
            std::pair{std::make_shared<BernoulliThompson>(this->pool_), "sampling"}
        };

        auto regretPlot = std::make_shared<sciplot::Plot>();
        auto rewardPlot = std::make_shared<sciplot::Plot>();
        auto ctrPlot = std::make_shared<sciplot::Plot>();

        regretPlot->palette("set1");
        rewardPlot->palette("set1");
        ctrPlot->palette("set1");

        regretPlot->size(1024, 720);
        rewardPlot->size(1024, 720);
        ctrPlot->size(1024, 720);

        std::vector<int>    time;
        std::vector<double> totalRegretCount;
        std::vector<double> totalRewardCount;
        std::vector<double> ctr;

        for (auto [algorithm, name] : algorithms) {
            for (auto i = 0; i < this->n_; ++i) {
                const auto statistics = algorithm->Execute();

                totalRegretCount.push_back(statistics->GetTotalRegret());
                totalRewardCount.push_back(statistics->GetTotalReward());

                auto tempCtr = statistics->GetRewardRate(statistics->GetLocalOptimalBanditIndex());
                if (tempCtr == std::numeric_limits<double>::infinity()) {
                    tempCtr = 0.0;
                }
                ctr.push_back(tempCtr);

                time.push_back(i + 1);
            }

            // total regret
            regretPlot->drawCurveWithPoints(time, totalRegretCount)
                .label(std::format("{}", name));
            totalRegretCount.clear();

            // total reward
            rewardPlot->drawCurveWithPoints(time, totalRewardCount)
                .label(std::format("{}", name));
            totalRewardCount.clear();

            // ctr
            ctrPlot->drawCurveWithPoints(time, ctr)
                .label(std::format("CTR {}", name));
            ctr.clear();

            time.clear();

            const auto statistics = algorithm->GetStats();

            std::cout << std::format("Name: {}\n", name);
            std::cout << std::format("Total atempts: {}\n", statistics->GetTotalChoose());
            std::cout << std::format("Total reward: {}\n", statistics->GetTotalReward());
            std::cout << std::format("Total regret: {}\n\n", statistics->GetTotalRegret());

            for (auto j = 0; j < statistics->GetPoolSize(); ++j) {
                const auto bandit = statistics->GetPool()->GetBandit(j);

                std::cout << std::format("Arm \"{}\" ({:.2f}%)\n", bandit->GetName(), bandit->GetProbability() * 100.0);
                std::cout << std::format("Reward count: {}\n", statistics->GetRewardCount(j));
                std::cout << std::format("Reward rate: {:.2f}%\n", statistics->GetRewardRate(j) * 100.0);
                std::cout << std::format("Choose count: {}\n", statistics->GetChooseCount(j));
                std::cout << std::format("Choose rate: {:.2f}%\n", statistics->GetChooseRate(j) * 100.0);
                std::cout << std::format("------------------------\n");
            }
            std::cout << std::format("Optimal arm \"{}\" and it's {}\n",
                statistics->GetPool()->GetBandit(statistics->GetLocalOptimalBanditIndex())->GetName(),
                statistics->GetLocalOptimalBanditIndex() == statistics->GetTrueOptimalBanditIndex() ?
                "TRUE" : "FALSE");
            std::cout << std::format("========================================\n");
        }

        auto x = sciplot::linspace(1, this->n_, 1);
        regretPlot->drawCurve(x, std::log(x)).label("log(x)").lineColor("black").lineWidth(4);

        this->DrawPlots(regretPlot, rewardPlot, ctrPlot);
    }
};
