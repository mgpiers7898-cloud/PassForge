#include "PassForge.hpp"
#include "Hash.hpp"

class Vault
{
private:
    std::size_t sizeAlloc_{};
    std::vector<std::pair<bool, std::string>> buffer_{};


public:
    void setBuffSize(std::size_t size);
    void add(const std::string& pass);
};
