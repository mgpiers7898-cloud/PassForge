#include "BruteForce.hpp"

std::string Result::out()
{
    if (this->check())
    {
        const int errCode = 1;
        return errHand.at(errCode);
    }

    std::string result = std::format
        ("ENTROPY : {}\nRATE: {} \nGPU: {} \nTAGERTHASH : {}\n ESTIMATION : {}\n", 
            this->entropy_, this->rate_, this->GPUModRoN(), this->targetHash_, this->estimatedTime_.getTheTime());

    return result;
}