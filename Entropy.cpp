#include "PassForge.hpp"
#include "Hash.hpp"
#include <iostream>
double Entropy::estimate(std::string_view pass, std::size_t poolSize)
{
    return static_cast<double>(pass.size() * std::log2(poolSize));
}

Entropy::CheckTime::CheckTime(std::size_t y, std::size_t d,
                              std::size_t h, std::size_t m, std::size_t s, long double ts) : years_(y), days_(d), hours_(h), minutes_(m), seconds_(s), totalSec_(ts)
{
}

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
[[nodiscard]] Entropy::GPUPower Entropy::query()
{
    static GPUPower cached{};
    static bool done = false;
    if (done)
        return cached;

    IDXGIFactory1 *factory = nullptr;
    HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1),
                                    reinterpret_cast<void **>(&factory));
    if (FAILED(hr))
        return {};

    IDXGIAdapter *adapter = nullptr;
    hr = factory->EnumAdapters(0, &adapter);
    if (FAILED(hr))
    {
        factory->Release();
        return {};
    }

    DXGI_ADAPTER_DESC desc = {};
    hr = adapter->GetDesc(&desc);
    if (FAILED(hr))
    {
        adapter->Release();
        factory->Release();
        return {};
    }

    char narrow[128] = {};
    WideCharToMultiByte(CP_UTF8, 0, desc.Description, -1,
                        narrow, sizeof(narrow), nullptr, nullptr);

    cached.model_ = narrow;
    cached.vram_ =
        desc.DedicatedVideoMemory > 0 ? desc.DedicatedVideoMemory : desc.SharedSystemMemory;

    switch (desc.VendorId)
    {
    case 0x10DE:
        cached.vendor_ = "NVIDIA";
        break;
    case 0x1002:
        cached.vendor_ = "AMD";
        break;
    case 0x8086:
        cached.vendor_ = "Intel";
        break;
    default:
        cached.vendor_ = "Unknown";
    }

    adapter->Release();
    factory->Release();

    done = true;
    return cached;
}

// HEH!...!
[[nodiscard]] Entropy::GPUPower Entropy::parseGPU(std::string_view name)
{
    auto n = lower(name);
    GPUPower r;
    if (name.empty())
    {
        r.vendor_ = "cpu";
        return r;
    }
    if (n.find("nvidia") != std::string_view::npos)
        r.vendor_ = "NVIDIA";
    else if (n.find("radeon") != std::string_view::npos)
        r.vendor_ = "AMD";
    else if (n.find("intel") != std::string_view::npos)
        r.vendor_ = "Intel";
    else
        r.vendor_ = "Unknown";

    return r;
}

std::string Entropy::tierOf(std::size_t gb)
{
    auto it = GPUTierMap.lower_bound(gb);
    if (it != GPUTierMap.end())
        return it->second.data();
    return "very_high";
}

[[nodiscard]] double Entropy::estimateRate(HashType type)
{
    // we are here with this shit error !
    auto p = query();
    auto gb = p.vram_;
    std::string_view tier = tierOf(gb);

    const auto& rit = TierRateMap.find(tier);
    if (rit == TierRateMap.end())
        return 100e6;
    const auto &r = rit->second;
    double base = (type == HashType::MD5)    ? r.md5_ 
                : (type == HashType::SHA512) ? r.sha512_
                : r.sha256_;

    double factor = 1.0;
    if(p.vendor_ == "AMD") factor = 0.9;
    if(p.vendor_ == "Intel") factor = 0.3;

    return base * factor;
}

std::vector<std::string> Entropy::BF_Details::parseMask(std::string_view mask)
{
    std::vector<std::string> charsets{};
    std::string charset{};
    std::size_t i{};
    while(i < mask.size())
    {
        if (mask[i] == '?' && i + 1 < mask.size())
        {
            char token = mask[i + 1];
            auto it = BF_Details::parMaskTable.find(token);
            charsets.push_back(it != BF_Details::parMaskTable.end() ?
                               it->second : "");
            i += 2;
        }
        else
        {
            charsets.push_back(std::string(1, mask[i]));
            i += 1;
        }
    }
    return charsets;
}

std::size_t Entropy::BF_Details::keySpaceOf(const std::vector<std::string>& charsets)
{
    std::size_t total = 1;
    for(auto& i : charsets)
    {
        if(i.empty()) return 0;
        if(total < SIZE_MAX / i.size()) return 0;
        total *= i.size();
    }
    return total;
}

Entropy::CheckTime Entropy::BF_Details::secondsToCheckTime(double totalSec)
{
    CheckTime t;
    constexpr double SEC_PER_YEAR = 31'536'000.0;
    constexpr double SEC_PER_DAY = 86'400.0;
    constexpr double SEC_PER_HOUR = 3'600.0;
    constexpr double SEC_PER_MIN = 60.0;

    double rem = totalSec;

    t.years_ = static_cast<std::size_t>(rem / SEC_PER_YEAR);
    rem = std::fmod(rem, SEC_PER_YEAR);

    t.days_ = static_cast<std::size_t>(rem / SEC_PER_DAY);
    rem = std::fmod(rem, SEC_PER_DAY);

    t.hours_ = static_cast<std::size_t>(rem / SEC_PER_HOUR);
    rem = std::fmod(rem, SEC_PER_HOUR);

    t.minutes_ = static_cast<std::size_t>(rem / SEC_PER_MIN);
    rem = std::fmod(rem, SEC_PER_MIN);

    t.seconds_ = static_cast<std::size_t>(rem);

    return t;
}

[[nodiscard]] Entropy::EntropyInfo Entropy::estimateFor
    (std::size_t keySpace, HashType type)
{
    EntropyInfo info;
    info.keySpace_ = keySpace;

    if(keySpace == 0)
    {
        info.EntropyBits_ = 0.0;
    }
    else
    {
        info.EntropyBits_ = std::log2(static_cast<double>(keySpace));
    }
    info.rate_ = estimateRate(type);
    if(info.rate_ > 0)
    {
        double seconds = static_cast<double>(keySpace) / info.rate_;
        info.estimatedTime_ = BF_Details::secondsToCheckTime(seconds);
    }
    return info;
}
