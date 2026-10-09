#pragma once

#include <windows.h>
#include <cstdint>
#include <bcrypt.h>

namespace RNG_Req
{
    template <typename Container>
    inline void giveMeSomeBytes(Container &buffer, std::size_t size)
    {
        BCryptGenRandom(nullptr, reinterpret_cast<UCHAR*>(&buffer), 
                        size, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    }
}

class BOF
{
private:
    std::uint64_t state_;
public:

    inline BOF() : state_(0) 
    {
        RNG_Req::giveMeSomeBytes(state_, 8);
    }

    inline std::uint64_t next()
    {
        state_ ^= state_ << 13;
        state_ ^= state_ >> 7;
        state_ ^= state_ << 17;
        return state_;
    }

    inline void fill(std::uint8_t* buf, std::size_t size)
    {
        for(std::size_t i{}; i < size; i++)
        {
            buf[i] = static_cast<std::uint8_t>(next());
        }
    }

    inline void OVF(std::uint8_t *buf, std::size_t size, std::size_t ext = 64)
    {
        fill(buf, size + ext);
    }
};
