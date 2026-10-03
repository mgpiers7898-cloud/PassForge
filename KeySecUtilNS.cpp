#include "KeySec.hpp"

std::array<std::uint8_t, 8> SecUtils::getBytes()
{
    std::array<std::uint8_t, 8> buffer{};

        BCryptGenRandom(nullptr,
                        buffer.data(),
                        buffer.size(),
                        BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    return buffer;
}

std::array<std::uint8_t, 8> SecUtils::unicode()
{
    std::array<std::uint8_t, 8> buffer{};
    BCryptGenRandom(nullptr,
                    buffer.data(),
                    buffer.size(),
                    BCRYPT_USE_SYSTEM_PREFERRED_RNG);

    std::array<std::uint8_t, 8> utf8{};

    utf8[0] = static_cast<std::uint8_t>((buffer[0] & 0x07) | 0xF0);
    utf8[1] = static_cast<std::uint8_t>((buffer[1] & 0x3F) | 0x80);
    utf8[2] = static_cast<std::uint8_t>((buffer[2] & 0x3F) | 0x80);
    utf8[3] = static_cast<std::uint8_t>((buffer[3] & 0x3F) | 0x80);
    utf8[4] = static_cast<std::uint8_t>((buffer[4] & 0x07) | 0xF0);
    utf8[5] = static_cast<std::uint8_t>((buffer[5] & 0x3F) | 0x80);
    utf8[6] = static_cast<std::uint8_t>((buffer[6] & 0x3F) | 0x80);
    utf8[7] = static_cast<std::uint8_t>((buffer[7] & 0x3F) | 0x80);

    std::fill(buffer.begin(), buffer.end(), 0);

    return utf8;
}

