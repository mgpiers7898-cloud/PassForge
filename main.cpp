#include "PassForge.hpp"
#include "Facade.hpp"
#include <iostream>
int main()
{
	PassForge prp;
	prp.runPrompt();
	std::cout <<prp.entropy() <<'\n';
	std::cout <<prp.hash() <<'\n';
	prp.saveInFile();
	std::cout << prp.crackTime(100'000'000) <<'\n';
}