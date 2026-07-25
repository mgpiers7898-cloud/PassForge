#include"PassForge.hpp"
#include<iostream>

int main()
{
	std::cout << Generator::mixPasscode(40) << '\n';
	std::cout << Generator::policyBasedPasscode(PolicyRules::TooStrong) << '\n';
}