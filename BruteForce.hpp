#pragma once

#include "Hash.hpp"
#include "PassForge.hpp"

struct Result
{
    std::string password_{};
    double time_{};
    double rate_{};
    double entropy_{};
    Entropy::CheckTime estimatedTime_{};
};

namespace BF
{

};

