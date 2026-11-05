#include "Facade.hpp"
#include "Hash.hpp"
#include <iostream>
void PassForge::setOptions()
{
    std::uint32_t wrapper;
    PoolType type; PolicyRules ruleSet;
    std::cout << "Enter type and press enter (1,...,12)";
    std::cin >> wrapper;
    switch(wrapper)
    {
        case 1 :
            type = PoolType::ASCII; break;
        case 2 :
            type = PoolType::HexLower; break;
        case 3 :
            type = PoolType::HexUpper; break;
        case 4 :
            type = PoolType::Binary; break;
        case 5 :
            type = PoolType::Octal; break;
        case 6 :
            type = PoolType::Base32; break;
        case 7 :
            type = PoolType::Base64; break;
        case 8 :
            type = PoolType::Base64URL; break;
        case 9 :
            type = PoolType::Vowels; break;
        case 10 :
            type = PoolType::Consonants; break;
        case 11:
            type = PoolType::All; break;
        case 12:
            type = DefaultPool; break;
        default:
            type = DefaultPool;
        }
    std::cout << "Enter ruleSet and press enter(1,...,4) ";
    std::cin >> wrapper;
    switch(wrapper)
    {
        case 1 : 
            ruleSet = PolicyRules::TooStrong; break;
        case 2 : 
            ruleSet = PolicyRules::Strong; break;
        case 3 : 
            ruleSet = PolicyRules::Medium; break;
        case 4 : 
            ruleSet = PolicyRules::Simple; break;
        default :
            ruleSet = PolicyRules::Strong; break;
    }
    auto res = Generator::generateByPolicy(type, ruleSet);

    if (res)
    {
        auto [pass, size] = res.value();
        this->pass_ = pass.value();
        this->size_ = size;
        this->SetOPDONE_ = true;
    }
}

void PassForge::generateFlow()
{
    if(this->SetOPDONE_)
    {
        std::cout << "Pass : " << this->pass_ <<'\n';
        std::cout << "Length : " << this->size_ <<'\n';
        return;
    }
    this->setOptions();
    std::cout << "Pass : " << this->pass_ << '\n';
    std::cout << "Length : " << this->size_ << '\n';
}

void PassForge::hashFlow()
{
    if(this->SetOPDONE_)
    {
        std::uint8_t c{};
        std::cout << "Enter The HashType:(1 sha256, 2 sha512, 3 MD5) :";
        std::cin >> c;

        auto res = Hash::hasher(this->pass_, (HashType)c);
        std::cout << "Pass : " << this->pass_ << "Hash : " << res <<'\n';
        return;
    }
    std::cerr << "SetOptions operation not done! \n";
}

void PassForge::estimateFlow()
{
    if(!this->SetOPDONE_)
    {
        std::cout << "Please Generate a password first!\n";
        return;
    }
    double bits = Entropy::estimate(pass_, size_);
    std::cout << "Pass: " << pass_ <<'\n';
    std::cout << "Entropy: " << bits <<'\n';

    std::cout << "Estimated Crack Time : \n";
    double com = std::pow(2.0, bits);
    double rate = Entropy::cpuRate(HashType::SHA256);
    double sec = com / rate;
    std::cout << "Crack Time (SHA256, CPU-Based BF): " <<
        Entropy::BF_Details::secondsToCheckTime(sec) << std::endl; 
}

void PassForge::crackFlow()
{
    if(!this->SetOPDONE_)
    {
        std::cout << "Please Generate a password first!\n";
        return;
    }
    std::string hash, mask;
    std::uint8_t type;
    std::cout << "Options : hash - mask - type(1,2,3): ";
    std::cin >> hash >> mask >> type;
    if(hash.empty() || mask.empty() || type == 0)
    {
        std::cerr << "\nEmpty hash or mask or 0 type\n";
        return;
    }
    auto res = BF::run(hash, mask, (HashType)type);
    std::cout << res.value() <<'\n';
    if(res.value().password_.empty())
    {
        std::cout << "\nFailed To Crack!\n";
    }
}

void PassForge::saveFlow()
{
    std::ofstream o("passforge.txt", std::ios::app);
    o   << "pass: "   << pass_ << '\t' << "len: " << size_ 
        << "SHA256: " << Hash::hasher(pass_, HashType::SHA256) << '\n'
        << "SHA512: " << Hash::hasher(pass_, HashType::SHA512) << '\n'
        << "MD5 : "   << Hash::hasher(pass_, HashType::MD5)    <<'\n';
}

void PassForge::runPrompt()
{
    while(true)
    {
        std::cout << "\n=== PASSFORGE v1.0 (made by piera) ===\n";
        std::cout << "for preventing from crash or error please do the 0 first\n";
        std::cout << "0 : set options\n";
        std::cout << "1 : generate password\n";
        std::cout << "2 : hash a password\n";
        std::cout << "3 : estimate entropy\n";
        std::cout << "4 : crack a hash\n";
        std::cout << "5 : save last password\n";
        std::cout << "6 : Exit\n";

        int choice;

        std::cin >> choice;

        switch(choice)
        {
            
        }
    }
}






