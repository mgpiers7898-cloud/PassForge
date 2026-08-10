#include "PassForge.hpp"
// Only the OS Seed can be really random like for satisfies the Entropy making:
std::uint32_t Engine::SecureEngine::operator()()
{
    std::uint32_t result;
    BCryptGenRandom(nullptr, reinterpret_cast<UCHAR *>(&result), sizeof(result),
                    BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    return result;
}

Engine::SecureEngine &Engine::getEngine()
{
    static Engine::SecureEngine engine;
    return engine;
}