#pragma once

#include "Hash.hpp"
#include <cstdint>
#include <iostream>
#include <format>
#include <cstring>
#include "PassForge.hpp"
#include "UnicodeUtils.hpp"

struct uint512_t
{
    std::uint64_t parts_[8];

    // STORING AND LOADING
    inline static std::uint64_t load64(const std::uint8_t *x)
    {
        std::uint64_t r = 0;
        for (std::size_t i = 0; i < 8; i++)
            r |= (std::uint64_t)x[i] << (8 * i);
        return r;
    }
    inline static void store64(std::uint8_t *x, std::uint64_t u)
    {
        for (std::size_t i = 0; i < 8; i++)
            x[i] = (u >> (8 * i) & 0xFF);
    }

    inline static uint512_t load512(const std::uint8_t *x)
    {
        uint512_t r{};
        for (std::size_t i = 0; i < 8; i++)
            r.parts_[i] = load64(x + i * 8);
        return r;
    }

    inline static void store512(std::uint8_t *x, const uint512_t &u)
    {
        for (std::size_t i = 0; i < 8; i++)
        {
            store64(x + i * 8, u.parts_[i]);
        }
    }

    // OPERATORS
    inline bool operator==(const uint512_t &x) const
    {
        std::uint64_t diff = 0;
        for (std::size_t i{}; i < 8; i++)
            diff |= this->parts_[i] ^ x.parts_[i];
        return diff == 0;
    }
    inline uint512_t operator^(const uint512_t &x) const
    {
        uint512_t res{};
        for (std::size_t i{}; i < 8; i++)
        {
            res.parts_[i] = this->parts_[i] ^ x.parts_[i];
        }
        return res;
    }
    inline uint512_t &operator^=(const uint512_t &x)
    {
        for (std::size_t i{}; i < 8; i++)
        {
            this->parts_[i] ^= x.parts_[i];
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const uint512_t &obj)
    {
        for (std::size_t i{}; i < 8; i++)
        {
            out << std::format("{:016x}", obj.parts_[i]);
        }
        return out;
    }
};

struct Key512
{

    uint512_t key_{};

    inline void toHex() const
    {
        for (std::size_t i{}; i < 8; i++)
        {
            std::cout << this->key_ << '\n';
        }
    }
    inline bool operator==(const Key512 &k) const
    {
        return this->key_ == k.key_;
    }
};

namespace SecUtils
{
    std::array<std::uint8_t, 8> getBytes(); // Layer one
    std::array<std::uint8_t, 8> unicode();

    inline decltype(auto) xorVal(std::uint64_t DK) // Layer three oper
    {
        std::array<std::uint8_t, 8> token{};

        auto bytes = getBytes();
        auto unicodes = unicode();

        auto *dkBy = reinterpret_cast<std::uint8_t *>(&DK);

        for (std::size_t i{}; i < 8; i++)
        {
            token[i] = dkBy[i] ^ bytes[i] ^ unicodes[i];
        }
        return token;
    }

    inline constexpr std::uint64_t kGB = 0x99AABBCCDDEEFF00ULL;
}

class KeySec
{
private:

    inline std::uint64_t iter512() // Layer three DK for Make it XOR
    {
        static std::uniform_int_distribution<std::size_t> dist(0, 7);
        return this->globKey_.parts_[dist(Engine::getEngine())];
    }

    inline bool isRemoteDebuggerPresent()
    {
        BOOL flag = FALSE;
        CheckRemoteDebuggerPresent(GetCurrentProcess(), &flag);
        return flag != FALSE;
    }

    void genTMPKey();

    uint512_t globKey_{};
    std::uint64_t tempKey_{};

public:
    void setGlobPass(std::string_view pass);

    // void showOnce();

    // bool check();
};
