#include "PassForge.hpp"
#include <iostream>
#include<Windows.h>
int main()
{
	std::cout << Generator::generateByPolicy(PoolType::Base64 | PoolType::Base32 | PoolType::Binary | PoolType::ASCII, PolicyRules::TooStrong).value();
}