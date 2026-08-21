#include "PassForge.hpp"
#include "Facade.hpp"
int main()
{
	PassForge prp;
	prp.runPrompt();
	prp.entropy();
	prp.hash();
	prp.saveInFile();
}