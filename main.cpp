#include "PassForge.hpp"
#include <iostream>
#include "UnicodeUtils.hpp"
#include <fstream>
int main()
{
	auto prop = Generator::generateByPolicy(PoolType::ASCII  | PoolType::Base64, PolicyRules::Medium);
	std::string pass = Pool::Utilities::extractPass(prop).value();
	std::size_t passSize = Pool::Utilities::extractSize(prop).value();

	std::cout << pass <<'\n';
	std::cout << passSize <<'\n';

	auto res = Entropy::estimate(pass, passSize);
	std::cout << res <<'\n';

	std::cout << Entropy::showTheEstimateTime(res, 1000000) <<'\n';
}