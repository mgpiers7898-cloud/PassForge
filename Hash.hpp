#include "PassForge.hpp"
#include <unordered_map>

namespace Hash
{
    std::string sha256(std::string_view pass);
    void toFile(std::string_view hash, const std::string &path);
    inline constexpr std::uint64_t kGC = 0x0F0F0F0F0F0F0F0FULL;
    std::string sha512(std::string_view pass);
    std::array<std::uint8_t, 64> sha512Raw(std::string_view pass);
}