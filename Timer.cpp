#include "Timer.hpp"

void Timers::countdown(std::size_t combos, std::size_t keySpace,
                       double elapsedSeconds)
{
    if (elapsedSeconds <= 0)
        return;

    double rate = combos / elapsedSeconds;
    double remaining = (keySpace - combos) / rate;
    std::size_t totalSecs = static_cast<std::size_t>(remaining);
    std::size_t hrs = totalSecs / 3600;
    std::size_t mins = (totalSecs % 3600) / 60;
    std::size_t secs = totalSecs % 60;

    double percent = combos * 100.0 / keySpace;

    std::cout << "\r["
              << std::fixed << std::setprecision(2) << percent << "%] "
              << combos << "/" << keySpace
              << " | " << std::scientific << std::setprecision(2) << rate
              << " H/s"
              << " | ETA: "
              << std::setw(4) << std::setfill('0') << hrs
              << ":"
              << std::setw(2) << std::setfill('0') << mins
              << ":"
              << std::setw(2) << std::setfill('0') << secs
              << std::flush;
}