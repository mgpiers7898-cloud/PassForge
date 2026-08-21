#include "PassForge.hpp"
#include <iostream>
std::string Hash::sh256(std::string_view pass)
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
    for(const auto& hex : hashBytes)
    {
        outHex.append(std::format("{:02x}", hex));
    }

    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlgorithm, 0);

    return outHex;
}

void Hash::toFile(std::string_view hash, const std::string& path = ".PassForge.txt")
{
    std::ofstream out(path, std::ios::app);
    out << hash <<'\n';

    if(!out)
    {
        std::cerr << "\nFailed to open file!\n";
    }
    else
    {
        std::cout << "DONE!";
    }
}