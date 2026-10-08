#include "KeySec.hpp"

std::vector<KeySec::WatchEntry> KeySec::hitList_;
HANDLE KeySec::threadHND_ = nullptr;
std::atomic<bool> KeySec::armed_ = false;

void KeySec::armWd()
{
    if (KeySec::armed_)
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
    for (std::size_t i{}; i < sizeof(wtchTrgt) / sizeof(wtchTrgt[0]); i++)
    {
        auto target = wtchTrgt[i];
        VirtualQuery(target, &mbi, sizeof(mbi));
        void *base = mbi.BaseAddress;
        std::size_t size = mbi.RegionSize;

        sum = Pool::Utilities::checksum(base, size);
        KeySec::hitList_.push_back({base, size, sum});
    }
    KeySec::armed_ = true;
    std::cout << "Before CreateThread" << std::endl;
    KeySec::threadHND_ = CreateThread(nullptr, 0,
        KeySec::wdEntry, nullptr, 0, nullptr);
    std::cout << "Thread handle: " << threadHND_ << std::endl;
    if (threadHND_ == nullptr)
    {
        std::cout << "Thread creation failed: " << GetLastError() << '\n';
    }
}

DWORD WINAPI KeySec::wdEntry(LPVOID param)
{
    std::cout << "wdEntry running" << std::endl;
    wdLoop();
    return 0;
}

void KeySec::wdLoop()
{
    while(armed_)
    {
        Sleep(3000);
        std::cout << "Searching!\n";
        if(compromised()) detonate();
        
    }
}

void KeySec::detonate()
{
}

bool KeySec::compromised()
{
    for(const auto& tar: hitList_)
    {
        if(tar.checkum_ != Pool::Utilities::checksum(tar.addr_, tar.size_))
            return true;
    }
    return false;
}