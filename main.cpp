#include <iostream>
#include "PassForge.hpp"
#include "BruteForce.hpp"
int main()
{
    std::string pass = "so";
    auto res = BF::run(Hash::md5(pass), "?a?a", HashType::MD5);
    std::cout << res.value().entropy_ << '\n';
    std::cout << res.value().estimatedTime_ << '\n';
    std::cout << res.value().password_ << '\n';
    std::cout << res.value().rate_ << '\n';
    std::cout << res.value().targetHash_ << '\n';
    std::cout << res.value().time_ << '\n';
}