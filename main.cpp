#include "PassForge.hpp"
#include <iostream>
int main()
{
	auto pass = Engine::generateByPolicy(PoolType::All, PolicyRules::TooStrong).value();

	std::cout << pass.size() << '\n';
	std::cout << Pool::Utilities::AllPoolSize() << '\n';
	std::cout << Entropy::estimate(pass, Pool::Utilities::AllPoolSize());
}