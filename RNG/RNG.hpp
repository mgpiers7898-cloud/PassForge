#pragma once
#include <cstdint>
#include <cstddef>
#include <algorithm>
namespace RNG
{
    namespace Detail
    { // anonymous namespace starts

        struct BotanURBG
        {
            using result_type = std::uint32_t;
            static constexpr std::uint32_t min() { return 0; }
            static constexpr std::uint32_t max() { return UINT32_MAX; }
            std::uint32_t operator()();
        };

    }

    std::uint32_t random_uint32();

    template <typename Range>
    void shuffle(Range &range)
    {
        Detail::BotanURBG engine;
        shuffle(range.begin(), range.end(), engine);
    }

    template <typename Range, typename OutputIt>
    void sample(const Range &source, OutputIt dest, std::size_t count)
    {
        Detail::BotanURBG engine;
        sample(source.begin(), source.end(), dest, count, engine);
    }

}