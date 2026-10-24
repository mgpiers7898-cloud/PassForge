#include <iostream>
#include "PassForge.hpp"
int main()
{
    auto res = Entropy::parseGPU(Entropy::GPUModRoN());
    std::cout << res.vendor_ <<'\n';
}