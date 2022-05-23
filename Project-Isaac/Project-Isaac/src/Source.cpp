#include "pch/pch.hpp"

#include "BanditPool/BanditPool.hpp"

#include "BanditTest/Tests/Test1.hpp"
#include "BanditTest/Tests/Test2.hpp"
#include "BanditTest/Tests/Test3.hpp"
#include "BanditTest/Tests/Test4.hpp"
#include "BanditTest/Tests/Test5.hpp"
#include "BanditTest/Tests/PracticeTest1.hpp"

int main(const int argc, char* argv[]) {
    constexpr auto iterations = 1;

    for (auto i = 0; i < iterations; ++i) {
        auto test = std::make_shared<PracticeTest1>(20'000);
        test->LaunchTest();
        std::cout << std::endl << std::endl;
    }
    
    return EXIT_SUCCESS;
}
