#include "PassForge.hpp"
#include <iostream>
#include "UnicodeUtils.hpp"
#include <fstream>
int main()
{
	auto pass = Generator::generateByPolicy(PoolType::ASCII | PoolType::Emoji | PoolType::Base64, PolicyRules::Strong).value();

	std::cout << pass.size() << '\n';
	std::cout << Pool::Utilities::AllPoolSize() << '\n';

	std::cout << Hash::sh256(pass) <<'\n';
	std::cout << pass <<'\n';
}