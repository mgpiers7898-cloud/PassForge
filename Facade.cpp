#include "Facade.hpp"
#include <iostream>
void PassForge::setPass(const std::string &pass)
{
    pass_ = pass;
}

void PassForge::setOptions(PoolType type, PolicyRules ruleSet)
{
    auto res = Generator::generateByPolicy(type, ruleSet);

    if (res)
    {
        auto [pass, size] = res.value();
        this->pass_ = pass.value();
        this->size_ = size;
    }
}

void PassForge::runPrompt()
{
    static constexpr const char *start =
        R"(___This Program is For Password Utilities____
           Input whatever will ask you .... >)";

    std::cout << '\n'
              << start << '\n';

    std::string type, rule;

    std::cout << "Type of your Pool (ASCII, HexL, HexU, Bin, Oct, B32, B64, B64U, Vow, Con, All): " << '\t';
    std::cin >> type;
    std::cout << "How Much Strong (TooStrong, Strong, Medium, Simple): " << '\t';
    std::cin >> rule;

    std::cout << R"(...Please Remember that your Pool
    Must satisfy your desire Password otherwise 
    please use default password generation....)";

    PoolType pools = poolTypeTable_.at(normalize(type));
    PolicyRules ruleSet = ruleSetTable_.at(normalize(rule));

    auto pass = Generator::generateByPolicy(pools, ruleSet).value();

    std::cout << "Please Copy Your Password" << '\n'
              << pass.pass_.value();
    this->pass_ = pass.pass_.value();
}

[[nodiscard]] std::string PassForge::hash()
{
    if (this->checkPass())
    {
        throw std::invalid_argument("No Password Generated!\n");
    }

    auto hashedPass = Hash::sh256(this->pass_);
    return hashedPass;
}

[[nodiscard]] double PassForge::entropy()
{
    return Entropy::estimate(this->pass_, this->size_);
}

std::string PassForge::crackTime(double guessPerSec)
{
    return Entropy::showTheEstimateTime(PassForge::entropy(), guessPerSec);
}

void PassForge::saveInFile(const std::string &path = ".PassForge.txt") const
{
    std::ofstream out(path, std::ios::app);
    if (this->pass_.empty())
    {
        std::cerr << "\nPassword Has Not Generated!\n";
        return;
    }
    if (out)
    {
        out << this->pass_ << '\t';
        out << Hash::sh256(this->pass_) << '\n';
    }
}
