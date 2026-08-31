#include "PassForge.hpp"
template <typename Container, typename HashAlgo>
class Vault
{
    Container buffer_;
    Hash encAlgo_(std::string_view pass);
    

public:
    void add(std::string_view pass, std::string_view lable);
    std::string get(std::string_view label);
    void save(const std::string &path);
    void load(const std::string &path);
};

class SHA256{};

using DefaultValue = Vault<std::vector<unsigned char>, SHA256>;

