#include "KeySec.hpp"
#include "bytes.hpp"

std::vector<KeySec::WatchEntry> KeySec::hitList_;
HANDLE KeySec::threadHND_ = nullptr;
std::atomic<bool> KeySec::poisoned_ = false;
std::atomic<bool> KeySec::armed_ = false;

void KeySec::armWd()
{
    if (KeySec::poisoned_)
        return;

    const void *wtchTrgt[] =
        {
            reinterpret_cast<const void *>(&Obf::apply),
            reinterpret_cast<const void *>(&Obf::xorMask),
            reinterpret_cast<const void *>(&SecUtils::xorVal),
            reinterpret_cast<const void *>(&SecUtils::getBytes),
            reinterpret_cast<const void *>(&Obf::getThreeRand),
            reinterpret_cast<const void *>(&SecUtils::unicode)};
    std::uint64_t sum{};
    MEMORY_BASIC_INFORMATION mbi;
    bool exists{};
    for (std::size_t i{}; i < 6; ++i)
    {
        auto target = wtchTrgt[i];
        VirtualQuery(target, &mbi, sizeof(mbi));

        for (const auto &e : hitList_)
            if (e.addr_ == mbi.BaseAddress)
            {
                exists = true;
                break;
            }
            if(!exists)
            {
                std::uint64_t sum = Pool::Utilities::checksum(mbi.BaseAddress, mbi.RegionSize);
                KeySec::hitList_.push_back({mbi.BaseAddress, mbi.RegionSize, sum});
            }
    }
    armed_ = true;
    threadHND_ = CreateThread(nullptr, 0,
                              KeySec::wdEntry, nullptr, 0, nullptr);
}

DWORD WINAPI KeySec::wdEntry(LPVOID param)
{
    wdLoop();
    return 0;
}

void KeySec::wdLoop()
{
    while (armed_)
    {
        Sleep(3000);
        if (compromised())
            neutralize();
    }
}

void KeySec::neutralize()
{
    BOF bof;

    bof.fill(reinterpret_cast<std::uint8_t *>(&globKey_),
             sizeof(globKey_));

    bof.fill(reinterpret_cast<std::uint8_t *>(&tempKey_),
             sizeof(tempKey_));

    poisoned_ = true;
    armed_ = false;
}

bool KeySec::compromised()
{
    for (const auto &tar : hitList_)
    {
        if (tar.checkum_ != Pool::Utilities::checksum(tar.addr_, tar.size_))
            return true;
    }
    return false;
}
