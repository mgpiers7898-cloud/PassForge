#include "RNG.hpp"
#include "botan/auto_rng.h"
namespace
{
    Botan::AutoSeeded_RNG &get_rng()
    {
        static Botan::AutoSeeded_RNG rng;
        return rng;
    }
}

std::uint32_t RNG::random_uint32()
{
    RNG::Detail::BotanURBG engine;
    return engine();
}

std::uint32_t RNG::Detail::BotanURBG::operator()()
{
    std::uint32_t result{};
    get_rng().randomize(
        reinterpret_cast<std::uint8_t *>(&result), sizeof(result));
    return result;
}
