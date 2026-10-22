#pragma once

#include "Hash.hpp"
#include "PassForge.hpp"
#include <iostream>
inline std::unordered_map<std::size_t, std::string> errHand
{
    {1, "Empty Hash"}
};

struct Result
{
    double entropy_;
    double rate_;
    bool GPUIsReady_;
    std::string targetHash_;
    Entropy::CheckTime estimatedTime_;
    
    Result() = default;
    Result(double e, double r, bool GIR, const std::string& tarH, 
        const Entropy::CheckTime eT) :
            entropy_(e), rate_(r), GPUIsReady_(GIR),
                targetHash_(tarH), estimatedTime_(eT)
    {
    }

    std::string out();
    inline bool check()
    {
        return this->targetHash_.empty();
    }
};

