#include "PassForge.hpp"
namespace Hash
{
    std::string sh256(std::string_view pass);
    void toFile(std::string_view hash, const std::string &path);
}