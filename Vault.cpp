#include "Vault.hpp"

void Vault::insert(std::string label, SecureBuffer data)
{
    hashInPlace(label, data);
    this->buffer_.emplace(std::move(label), std::move(data));
}

void Vault::hashInPlace(std::string& label, SecureBuffer& data)
{
    auto l = Hash::sha512(label);
    auto d = Hash::sha512(data.str());

    label = std::move(l);
    data.replace(std::move(d));

    std::fill(l.begin(), l.end(), 0);
    std::fill(d.begin(), d.end(), 0);
}

void Vault::add(std::string label, std::string_view pass)
{
    Vault::SecureBuffer secBuff(pass);
    this->insert(std::move(label), std::move(secBuff));
}

void Vault::rmv(const std::string& label)
{
    if(this->buffer_.contains(label))
    {
        this->buffer_.erase(label);
        return;
    }
    
    throw std::invalid_argument("\nNON_EXIST ITEM\n");
}

std::string Vault::getHashedPass(const std::string& label)
{
    return buffer_.at(label).str();
}

bool Vault::cmpr(std::string_view pass, const std::string& label)
{
    return this->buffer_.at(label).str() == pass;
}

bool Vault::check()
{
    // THE KEYSEC OPRATION MUST HAPPEND HERE 
}


