#include "Vault.hpp"

template<typename Container, typename HashAlgo>
void Vault<Container, HashAlgo>::add(std::string_view pass, std::string_view label)
{
    std::pair<std::string, std::string> table{};

    auto hashed = this->encAlgo_(pass);

    table.first = hashed;
    table.second = label;

    this->buffer_.push_back(table);
}