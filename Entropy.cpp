#include "PassForge.hpp"

double Entropy::estimate(std::string_view pass, std::size_t poolSize)
{
    return static_cast<double>(pass.size() * std::log2(poolSize));
}

Entropy::CheckTime::CheckTime(std::size_t y, std::size_t d,
    std::size_t h, std::size_t m, std::size_t s, long double ts):
        years_(y), days_(d), hours_(h), minutes_(m), seconds_(s), totalSec_(ts)
    {}

std::string Entropy::CheckTime::toString() const
{   
    std::string res{std::format("{}years, {}days, {}hours, {}minutes, {}seconds", 
        this->years_, this->days_, this->hours_,
        this->minutes_, this->seconds_)};

    return res;
}

std::string Entropy::CheckTime::getTheTime() const
{
    return toString();
}

std::string Entropy::showTheEstimateTime(double estimationBits, double guessPerSec)
{
    double combinations = std::exp2l(estimationBits);
    long double totalSeconds = combinations / guessPerSec;

    if (totalSeconds > 3.15576e12)
    {
        return "\nMore Than 100,000 Years! so Practically Ucrackable\n";
    }
    
    long double years = totalSeconds / 31536000.0L;
    long double remain = std::fmod(totalSeconds, 31536000.0L);

    long double days = remain / 86400.0L;
    remain = std::fmod(remain, 86400.0L);

    long double hours = remain / 3600.0L;
    remain = std::fmod(remain, 3600.0L);

    long double minutes = remain / 60.0L;
    remain = std::fmod(remain, 60.0L);

    long double seconds = remain;

    CheckTime time(
        (std::size_t)years,
        (std::size_t)days, 
        (std::size_t)hours, 
        (std::size_t)minutes,
        (std::size_t)seconds,
        totalSeconds);

    auto res = time.getTheTime();
    return res;
}