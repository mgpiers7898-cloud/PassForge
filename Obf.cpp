#include "Obf.hpp"

void Obf::xorMask(std::uint64_t &value, const std::uint64_t& mask)
{
    value ^= mask;
}
void Obf::rotl64InP(std::uint64_t &value, int n)
{
    value = std::rotl(value, n);
}
void Obf::combineInP(std::uint64_t &out,const std::uint64_t& b, const std::uint64_t& c)
{
    out ^= b; 
    out ^= c;
}