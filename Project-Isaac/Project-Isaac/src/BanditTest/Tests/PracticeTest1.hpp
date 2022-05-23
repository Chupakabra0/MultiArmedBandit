#pragma once

#include "BanditTest/Base/BanditTest.hpp"

#include <iostream>
#include <format>

class PracticeTest1 : public BanditTest {
public:
    //explicit PracticeTest1(int n)
    //    : BanditTest(std::make_shared<BanditPool>(std::initializer_list{
    //            std::make_shared<Bandit>(0.02, "1"),
    //            std::make_shared<Bandit>(0.1, "2")
    //        }
    //    ), n) {

    //}

    explicit PracticeTest1(int n)
        : BanditTest(std::make_shared<BanditPool>(std::initializer_list{
                std::make_shared<Bandit>(0.2, "1"),
                std::make_shared<Bandit>(0.05, "2"),
                std::make_shared<Bandit>(0.01, "3"),
                std::make_shared<Bandit>(0.001, "4"),
                std::make_shared<Bandit>(0.05, "5")
            }
            ), n) {

    }

    //explicit PracticeTest1(int n)
    //    : BanditTest(std::make_shared<BanditPool>(std::initializer_list{
    //            std::make_shared<Bandit>(0.01, "1"),
    //            std::make_shared<Bandit>(0.01, "2"),
    //            std::make_shared<Bandit>(0.05, "3"),
    //            std::make_shared<Bandit>(0.025, "4"),
    //            std::make_shared<Bandit>(0.05, "5")
    //        }
    //        ), n) {

    //}

    //explicit PracticeTest1(int n)
    //    : BanditTest(std::make_shared<BanditPool>(), n) {
    //    for (auto i = 1; i <= 20; ++i) {
    //        this->GetPool()->PushBandit(std::make_shared<Bandit>(0.01 * log(i), std::format("{}", i)));
    //    }
    //}

    void LaunchTest() override {
        auto algorithms = std::vector<std::pair<std::shared_ptr<BaseBanditAlgorithm>, std::string>>{
            //std::pair{std::make_shared<EpsilonKGreedy>(this->pool_, 0.1), "e_n-greedy(0.1)"},
            std::pair{std::make_shared<Softmax>(this->pool_, 0.1), "boltzmann(0.1)"},
            //std::pair{std::make_shared<Pursuit>(this->pool_, 0.25), "pursuit(0.25)"},
            //std::pair{std::make_shared<UCB1>(this->pool_), "UCB1"},
            //std::pair{std::make_shared<BernoulliThompson>(this->pool_), "thompson"},
        };

        auto regretPlot  = std::make_shared<sciplot::Plot>();
        auto rewardPlot  = std::make_shared<sciplot::Plot>();
        auto averagePlot = std::make_shared<sciplot::Plot>();
        auto probPlot    = std::make_shared<sciplot::Plot>();

        regretPlot->legend().atOutsideRight();
        rewardPlot->legend().atOutsideRight();
        averagePlot->legend().atOutsideRight();
        probPlot->legend().atOutsideRight();

        const auto theme = "dark2";
        regretPlot->palette(theme);
        rewardPlot->palette(theme);
        averagePlot->palette(theme);
        probPlot->palette(theme);

        regretPlot->size(1024, 720);
        rewardPlot->size(1024, 720);
        averagePlot->size(1024, 720);
        probPlot->size(1024, 720);

        std::vector<int>    time;
        std::vector<double> totalRegretCount;
        std::vector<double> totalRewardCount;
        std::vector<double> averageReward;
        std::vector<double> optimalRate;

        for (auto [algorithm, name] : algorithms) {
            for (auto i = 0; i < this->n_; ++i) {
                const auto statistics = algorithm->Execute();

                totalRegretCount.push_back(statistics->GetTotalRegret());
                totalRewardCount.push_back(statistics->GetTotalReward());

                auto optimal = statistics->GetRewardRate(statistics->GetLocalOptimalBanditIndex());
                if (optimal == std::numeric_limits<double>::infinity()) {
                    optimal = 0.0;
                }
                optimalRate.push_back(optimal);

                averageReward.push_back(static_cast<double>(statistics->GetTotalReward()) / statistics->GetTotalChoose());
                time.push_back(i + 1);

                if ((i + 1) % 2000 == 0) {
                    std::cout << std::format("Step: {}\n", i);
                    std::cout << std::format("Name: {}\n", name);
                    std::cout << std::format("Total attempts: {}\n", statistics->GetTotalChoose());
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

                    //system("pause");
                }
            }

            // total regret
            regretPlot->drawCurveWithPoints(time, totalRegretCount)
                .label(std::format("{}", name));
            totalRegretCount.clear();

            // total reward
            rewardPlot->drawCurveWithPoints(time, totalRewardCount)
                .label(std::format("{}", name));
            totalRewardCount.clear();

            // average reward
            averagePlot->drawCurveWithPoints(time, averageReward)
                .label(std::format("{}", name));
            averageReward.clear();

            probPlot->drawCurveWithPoints(time, optimalRate)
                .label(std::format("{}", name));
            optimalRate.clear();

            time.clear();

            const auto statistics = algorithm->GetStats();

            //std::cout << std::format("Name: {}\n", name);
            //std::cout << std::format("Total atempts: {}\n", statistics->GetTotalChoose());
            //std::cout << std::format("Total reward: {}\n", statistics->GetTotalReward());
            //std::cout << std::format("Total regret: {}\n\n", statistics->GetTotalRegret());

            //for (auto j = 0; j < statistics->GetPoolSize(); ++j) {
            //    const auto bandit = statistics->GetPool()->GetBandit(j);

            //    std::cout << std::format("Arm \"{}\" ({:.2f}%)\n", bandit->GetName(), bandit->GetProbability() * 100.0);
            //    std::cout << std::format("Reward count: {}\n", statistics->GetRewardCount(j));
            //    std::cout << std::format("Reward rate: {:.2f}%\n", statistics->GetRewardRate(j) * 100.0);
            //    std::cout << std::format("Choose count: {}\n", statistics->GetChooseCount(j));
            //    std::cout << std::format("Choose rate: {:.2f}%\n", statistics->GetChooseRate(j) * 100.0);
            //    std::cout << std::format("------------------------\n");
            //}
            //std::cout << std::format("Optimal arm \"{}\" and it's {}\n",
            //    statistics->GetPool()->GetBandit(statistics->GetLocalOptimalBanditIndex())->GetName(),
            //    statistics->GetLocalOptimalBanditIndex() == statistics->GetTrueOptimalBanditIndex() ?
            //    "TRUE" : "FALSE");
            //std::cout << std::format("========================================\n");
        }

        //auto x = sciplot::linspace(1, this->n_, 1);
        //regretPlot->drawCurve(x, std::log(x)).label("log(x)").lineColor("black").lineWidth(4);

        //this->DrawPlots(regretPlot, rewardPlot, averagePlot);
        //probPlot->show();
    }
};
