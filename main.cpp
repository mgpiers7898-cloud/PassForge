#include "PassForge.hpp"
#include <iostream>

int main()
{
    std::cout << Generator::policyBasedPasscode(PolicyRules::TooStrong) <<'\n';
}