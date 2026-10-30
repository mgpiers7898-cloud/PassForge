#include <iostream>
#include "PassForge.hpp"
#include "Hash.hpp"
#include "BruteForce.hpp"
int main()
{
    auto res = BF::run(Hash::md5(Generator::generatePassword(15)),"?l?l", HashType::MD5);
    std::cout << res.value().entropy_ <<'\n';
    std::cout << res.value().estimatedTime_ <<'\n';
    std::cout << res.value().password_ <<'\n' ;
    std::cout << res.value().rate_ <<'\n';
    std::cout << res.value().targetHash_ <<'\n';
    std::cout << res.value().time_ <<'\n';
}