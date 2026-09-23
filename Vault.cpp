#include "Vault.hpp"

void Vault::add(const std::string& pass, const std::string& key)
{
    this->buffer_.insert({pass, key});
}
void Vault::showStream(const std::string& key)
{
    std::cout << this->buffer_.find(key)->second << '\n';
}

std::string_view Vault::getPass(const std::string &key)
{
    std::string_view res = this->buffer_.find(key)->second;
    return res;
}
