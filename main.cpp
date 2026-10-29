#include <iostream>
#include "PassForge.hpp"
int main()
{
    auto info = Entropy::estimateFor(95ULL * 95 * 95 * 95 * 95 * 95, HashType::SHA256);
    // keySpace_ = ~7.35e11
    // EntropyBits_ ≈ 39.4
    // rate_ ≈ 1.08e9
    // estimatedTime_ = ~680 seconds = 11.3 minutes → 0y 0d 0h 11m 20s

    std::cout << info.EntropyBits_ << '\n' <<
        info.estimatedTime_ << '\n' <<
        info.keySpace_ << '\n' <<
        info.rate_ <<'\n';

    Entropy::CheckTime t{2, 45, 3, 12, 8, 0.0};
    std::cout << t << "\n";
    // 2years, 45days, 3hours, 12minutes, 8seconds

    Entropy::CheckTime z{};
    std::cout << z << "\n";
    // 0years, 0days, 0hours, 0minutes, 0seconds
}