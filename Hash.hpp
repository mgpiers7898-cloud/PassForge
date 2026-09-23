#include "PassForge.hpp"
#include <unordered_map>

namespace Hash
{
    std::string sha256(std::string_view pass);
    void toFile(std::string_view hash, const std::string &path);

    std::string sha512(std::string_view pass);
}