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

        friend std::ostream& operator<<(std::ostream& out, const Result& res)
        {
            out << "TARGET H:  "       << res.targetHash_
                << "PASSWORD : "       << res.password_
                << "TIME : "           << res.time_
                << "RATE : "           << res.rate_
                << "ENTROPY : "        << res.entropy_
                << "ESTIMATED TIME : " << res.estimatedTime_;

            return out;
        }
    };
    [[nodiscard]]std::optional<Result> run(std::string_view hash, std::string_view mask, HashType type);
}

