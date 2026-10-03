#pragma once

#include <cstdint>
#include <bit>

namespace Obf
{
    void xorMask(std::uint64_t& value,const std::uint64_t& mask);
    void rotl64InP(std::uint64_t& a, int n = 3);

    void combineInP(std::uint64_t &a,
        const std::uint64_t& b, const std::uint64_t& c);
}