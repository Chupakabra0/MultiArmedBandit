#pragma once

bool BoolRand(double);

int IntRand(int, int);
double RealRand(double, double);

template<class FIter, class SIter>
FIter::value_type Rand(FIter low, FIter high, SIter begin, SIter end) {
    const auto size = std::distance(low, high);
    std::vector<SIter::value_type> temp(size, 0.0);

    *temp.begin() = *begin++;
    for (auto i = 1; i < size; ++i) {
        temp[i] = temp[i - 1] + *begin++;
    }

    const auto rand = RealRand(0.0, *std::prev(temp.end()) - std::numeric_limits<SIter::value_type>::epsilon());
    const auto index = std::distance(temp.begin(), std::upper_bound(temp.begin(), temp.end(), rand));

    return *(low + index);
}
