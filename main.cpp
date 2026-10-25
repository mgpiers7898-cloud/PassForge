#include <iostream>
#include "PassForge.hpp"
int main()
{
    std::cout << Entropy::query().model_ <<'\n';
    std::cout << Entropy::getGPUVram() <<'\n';
}