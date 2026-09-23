#include "PassForge.hpp"
#include "Hash.hpp"
#include <iostream>
// FOR NOW THIS IS A SIMPLE VAULT NOT A REALLY HARD ONE BUT IT WILL BE A STRICT VAULT SOON!
class Vault
{
private:
    std::unordered_map<std::string, std::string> buffer_{};

public:
    void add(const std::string &pass, const std::string &key);
    void showStream(const std::string &key);
    std::string_view getPass(const std::string &key);
};
