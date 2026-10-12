#pragma once

#include <string>
#include <cstdint>
#include <string_view>
#include <fstream>
#include <windows.h>
#include "Hash.hpp"

namespace BruteForce
{
    struct Result
    {
        std::string password_{};
        double time_{};
        double rate_{};
        bool success_{};
        std::string error_{};

        double entropyBit_;
        std::string crkTimeEst_;
    };

    Result run(std::string_view hash, const std::string& mask, HashType type);

    std::string hasher(HashType type);

    std::string parseRes(Result&& res);
};