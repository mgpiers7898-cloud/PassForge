#include "Facade.hpp"
#include <iostream>
void PassForge::setPass(const std::string& pass)
{
    pass_ = pass;
}

void PassForge::setOptions(PoolType type, PolicyRules ruleSet)
{
    this->pass_ = Generator::generateByPolicy(type, ruleSet).value().pass_.value();
}

void PassForge::runPrompt()
{
    static constexpr const char* start = 
        R"(___This Program is For Password Utilities____
           Input whatever will ask you .... >)";

    std::cout << '\n' << start <<'\n';

    std::string type, rule; 

    std::cout << "Type of your Pool (ASCII, HexL, HexU, Bin, Oct, B32, B64, B64U, Vow, Con, All): " << '\t';
    std::cin >> type;
    std::cout << "How Much Strong (TooStrong, Strong, Medium, Simple): " <<'\t';
    std::cin >> rule;

    std::cout << R"(...Please Remember that your Pool
    Must satisfy your desire Password otherwise 
    please use default password generation....)";

    PoolType pools = poolTypeTable_.at(normalize(type));
    PolicyRules ruleSet = ruleSetTable_.at(normalize(rule));

    auto pass = Generator::generateByPolicy(pools, ruleSet).value();

    std::cout << "Please Copy Your Password";
    this->pass_ = pass.pass_.value();
}

std::string PassForge::hash()
{
    if(this->checkPass())
    {
        std::invalid_argument("No Password Generated!\n");
    }

    auto hashedPass = Hash::sh256(this->pass_);
    return hashedPass;
}
