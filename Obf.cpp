#include "Obf.hpp"

void Obf::xorMask(std::uint64_t &value, const std::uint64_t &mask)
{
    value ^= mask;
}
void Obf::rotl64InP(std::uint64_t &value, int n)
{
    value = std::rotl(value, n);
}
void Obf::combineInP(std::uint64_t &out, const std::uint64_t &b, const std::uint64_t &c)
{
    out ^= b;
    out ^= c;
}

std::uint64_t Obf::ROTL64(std::uint64_t x, int n)
{
    if (n == 0)
        return x;
    return (x << n) | (x >> (64 - n));
}

TripleVal Obf::getThreeRand()
{
    std::uniform_int_distribution<int> dist(5, 20);

    auto &eng = Engine::getEngine();

    return {dist(eng), dist(eng), dist(eng)};
}

void Obf::apply(std::uint64_t &tempKey, TripleVal values)
{
    auto &[r1, r2, r3] = values;

    __asm__ volatile(
        "movl %1, %%ecx\n\t"
        "rol %%cl, %0\n\t"

        "xor %2, %0\n\t"

        "mov %0, %%rax\n\t"
        "and $0xFF, %%rax\n\t"
        "xor %%rax, %0\n\t"

        "movl %3, %%ecx\n\t"
        "rol %%cl, %0\n\t"

        "mov %0, %%rax\n\t"
        "and $0xFFFF, %%rax\n\t"
        "xor %%rax, %0\n\t"

        "mov %0, %%rax\n\t"
        "shr $32, %%rax\n\t"
        "xor %%rax, %0\n\t"

        "movl %4, %%ecx\n\t"
        "rol %%cl, %0\n\t"

        : "+r"(tempKey)
        : "r"(r1), "r"(Pool::Utilities::kGA ^ 0xFFFFFF587353), "r"(r2), "r"(r3)
        : "rax", "rcx", "cc"
    );
}