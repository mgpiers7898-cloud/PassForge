#include <iostream>
#include "PassForge.hpp"
#include "KeySec.hpp"
int main()
{
    KeySec ks;
    ks.setGlobPass("test123");
    ks.showOnce();

    Sleep(5000); // let the watchdog tick

    // Corrupt a watched byte
    DWORD old;
    VirtualProtect(
        reinterpret_cast<void *>(&Obf::apply),
        1, PAGE_EXECUTE_READWRITE, &old);
    *reinterpret_cast<std::uint8_t *>(&Obf::apply) ^= 0xFF;
    VirtualProtect(
        reinterpret_cast<void *>(&Obf::apply),
        1, old, &old);

    Sleep(5000); // wait for detection

    return 0;
}