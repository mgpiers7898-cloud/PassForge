#pragma once

#include <cstdint>
#include <bit>
#include "PassForge.hpp"


struct TripleVal
{
    int f_, s_, t_;
};

namespace Obf
{
    void xorMask(std::uint64_t& value,const std::uint64_t& mask);
    void rotl64InP(std::uint64_t& a, int n = 3);

    void combineInP(std::uint64_t &a,
        const std::uint64_t& b, const std::uint64_t& c);

    TripleVal getThreeRand();

    std::uint64_t ROTL64(std::uint64_t x, int n);
    
    void apply(std::uint64_t& tempKey, TripleVal values);
}