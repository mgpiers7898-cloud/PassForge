#include <iostream>
#include "KeySec.hpp"
int main()
{
    auto res = SecUtils::unicodeConst();

    for(const auto& it : res)
    {
        std::cout << it;
    }
}