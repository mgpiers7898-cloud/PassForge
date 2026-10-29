#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>

namespace Timers
{
    void countdown(std::size_t combos, std::size_t keySpace,
                   double rate, double elapsedSeconds);
}