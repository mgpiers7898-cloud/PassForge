#include "PassForge.hpp"

double Entropy::estimate(std::string_view pass, std::size_t poolSize)
{
     return static_cast<double>(pass.size() * std::log2(poolSize));
}