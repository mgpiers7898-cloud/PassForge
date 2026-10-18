#include "Hash.hpp"
#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstddef>
std::string Hash::sha256(std::string_view pass)
{
    BCRYPT_HASH_HANDLE hHash = nullptr;
    BCRYPT_ALG_HANDLE hAlgorithm = nullptr;

    BCryptOpenAlgorithmProvider(
        &hAlgorithm,
        L"SHA256",
        nullptr,
        0);

    BCryptCreateHash(
        hAlgorithm,
        &hHash,
        nullptr,
        0,
        nullptr,
        0,
        0);

    BCryptHashData(
        hHash,
        reinterpret_cast<PUCHAR>(const_cast<char *>(pass.data())),
        static_cast<ULONG>(pass.size()),
        0);

    DWORD hashSize = 0;
    ULONG sizeLen = sizeof(DWORD);
    BCryptGetProperty(
        hAlgorithm,
        BCRYPT_HASH_LENGTH,
        reinterpret_cast<PUCHAR>(&hashSize),
        sizeof(DWORD),
        &sizeLen,
        0);

    std::vector<UCHAR> hashBytes(hashSize);
    BCryptFinishHash(hHash, hashBytes.data(), hashSize, 0);

    std::string outHex{};
    for (const auto &hex : hashBytes)
    {
        outHex.append(std::format("{:02x}", hex));
    }

    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlgorithm, 0);

    return outHex;
}

void Hash::toFile(std::string_view hash, const std::string &path = ".PassForge.txt")
{
    std::ofstream out(path, std::ios::app);
    out << hash << '\n';

    if (!out)
    {
        std::cerr << "\nFailed to open file!\n";
    }
    else
    {
        std::cout << "DONE!";
    }
}

std::string Hash::sha512(std::string_view pass)
{
    BCRYPT_HASH_HANDLE hHash = nullptr;
    BCRYPT_ALG_HANDLE hAlgorithm = nullptr;

    BCryptOpenAlgorithmProvider(
        &hAlgorithm,
        L"SHA512",
        nullptr,
        0);

    BCryptCreateHash(
        hAlgorithm,
        &hHash,
        nullptr,
        0,
        nullptr,
        0,
        0);

    BCryptHashData(
        hHash,
        reinterpret_cast<PUCHAR>(const_cast<char *>(pass.data())),
        static_cast<ULONG>(pass.size()),
        0);

    DWORD hashSize = 0;
    ULONG sizeLen = sizeof(DWORD);
    BCryptGetProperty(
        hAlgorithm,
        BCRYPT_HASH_LENGTH,
        reinterpret_cast<PUCHAR>(&hashSize),
        sizeof(DWORD),
        &sizeLen,
        0);

    std::vector<UCHAR> hashBytes(hashSize);
    BCryptFinishHash(hHash, hashBytes.data(), hashSize, 0);

    std::string outHex{};
    for (const auto &hex : hashBytes)
    {
        outHex.append(std::format("{:02x}", hex));
    }

    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlgorithm, 0);

    return outHex;
}

std::array<std::uint8_t, 64> Hash::sha512Raw(std::string_view pass)
{
    BCRYPT_HASH_HANDLE hHash = nullptr;
    BCRYPT_ALG_HANDLE hAlgorithm = nullptr;

    BCryptOpenAlgorithmProvider(
        &hAlgorithm,
        L"SHA512",
        nullptr,
        0);

    BCryptCreateHash(
        hAlgorithm,
        &hHash,
        nullptr,
        0,
        nullptr,
        0,
        0);

    BCryptHashData(
        hHash,
        reinterpret_cast<PUCHAR>(const_cast<char *>(pass.data())),
        static_cast<ULONG>(pass.size()),
        0);

    DWORD hashSize = 0;
    ULONG sizeLen = sizeof(DWORD);
    BCryptGetProperty(
        hAlgorithm,
        BCRYPT_HASH_LENGTH,
        reinterpret_cast<PUCHAR>(&hashSize),
        sizeof(DWORD),
        &sizeLen,
        0);

    std::array<std::uint8_t, 64> outHex{};
    BCryptFinishHash(hHash, outHex.data(), hashSize, 0);

    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlgorithm, 0);

    return outHex;
}

std::string Hash::md5(std::string_view pass)
{
    const std::uint8_t *data = reinterpret_cast<const uint8_t *>(pass.data());
    std::size_t len = pass.size();

    const constexpr std::uint8_t firstPadd = 0x80;
    const constexpr std::uint8_t secondPadd = 0x00;

    auto paddedLen = ((len + 8) / 64 + 1) * 64;
    std::vector<std::uint8_t> buffer(paddedLen, 0);
    std::uint64_t bitLen{len * 8};

    std::copy(data, data + len, buffer.begin());
    buffer[len] = firstPadd;
    for (std::size_t i{}; i < 8; ++i)
    {
        buffer[paddedLen - 8 + i] = (bitLen >> (8 * i)) & 0xFF;
    }

    std::uint32_t A{0x67452301}, B{0xefcdab89}, C{0x98badcfe}, D{0x10325476};

    for (std::size_t block{}; block < paddedLen; block += 64)
    {
        std::uint32_t M[16];
        for (int i = 0; i < 16; ++i)
        {
            M[i] = static_cast<std::uint32_t>(buffer[block + i * 4]) | (static_cast<std::uint32_t>(buffer[block + i * 4 + 1]) << 8) | (static_cast<std::uint32_t>(buffer[block + i * 4 + 2]) << 16) | (static_cast<std::uint32_t>(buffer[block + i * 4 + 3]) << 24);
        }

        std::uint32_t a = A, b = B, c = C, d = D;

        for (int i = 0; i < 64; ++i)
        {
            std::uint32_t f;
            if (i < 16)
                f = Hash::Detail::F(b, c, d);
            else if (i < 32)
                f = Hash::Detail::G(b, c, d);
            else if (i < 48)
                f = Hash::Detail::H(b, c, d);
            else
                f = Hash::Detail::I(b, c, d);

            std::uint32_t temp = d;
            d = c;
            c = b;
            b = b + Hash::Detail::rotl(
                        a + f + M[Hash::Detail::k[i]] + Hash::Detail::T[i],
                        Hash::Detail::s[i]);
            a = temp;
        }

        A += a;
        B += b;
        C += c;
        D += d;
    }
    auto toHex = [](std::uint32_t v)
    {
        std::string out{};
        for (int i{}; i < 4; ++i)
        {
            std::uint8_t byte = (v >> (8 * i)) & 0xFF;
            const char *hex = "0123456789abcdef";
            out += hex[byte >> 4];
            out += hex[byte & 0xF];
        }
        return out;
    };

    return toHex(A) + toHex(B) + toHex(C) + toHex(D);
}

[[nodiscard]] std::string Hash::hasher(std::string_view pass ,HashType type)
{
    switch(type)
    {
        case HashType::SHA256 : return sha256(pass);
        case HashType::SHA512 : return sha512(pass);
        case HashType::MD5    : return md5(pass);
    }
    return sha256(pass);
}
