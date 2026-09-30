#include <iostream>
#include "Hash.hpp"
#include <string>
#include <format>
int main()
{
    std::string some{"THERES SOMETHING TO SAY .... PIERA IS COMING!"};
    
    auto res = Hash::sha512Raw(some);

    for(const auto& it : res)
    {
        std::cout << std::format("{:02x}", it);
    }
}