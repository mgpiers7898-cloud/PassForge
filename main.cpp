#include "PassForge.hpp"
#include <iostream>

int main()
{
	std::cout << Generator::generateByPolicy(PolicyRules::TooStrong) << '\n';
}