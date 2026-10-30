#pragma once

#include "Hash.hpp"
#include "PassForge.hpp"
#include <chrono>
#include "Timer.hpp"

namespace BF
{
    struct Result
    {
        std::string targetHash_{};
        std::string password_{};
        double time_{};
        double rate_{};
        double entropy_{};
        Entropy::CheckTime estimatedTime_{};
    };
    [[nodiscard]]std::optional<Result> run(std::string_view hash, std::string_view mask, HashType type);
}

