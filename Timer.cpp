#include "Timer.hpp"

void Timers::countdown(std::size_t combos, std::size_t keySpace,
    double elapsedSeconds)
{
    if(elapsedSeconds <= 0)
        return;

    double rate = combos / elapsedSeconds;
    double remaining = (keySpace - combos) / rate;
    std::size_t mins = static_cast<std::size_t>(remaining) / 60;
    std::size_t secs = static_cast<std::size_t>(remaining) % 60;

    double percent = combos * 100.0 / keySpace;

    std::cout << "\r[" 
              << std::fixed << std::setprecision(2) << percent << "%] "
              << combos << "/" << keySpace
              << " | " << std::scientific << std::setprecision(2) << rate 
              << " H/s"
              << " | ETA: "
              << std::setw(2) << std::setfill('0') << mins
              << ":"
              << std::setw(2) << std::setfill('0') << secs
              << std::flush;
              
}