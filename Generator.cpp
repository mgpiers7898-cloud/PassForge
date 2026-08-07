#include "PassForge.hpp"
#include <iostream>
std::mt19937 &Generator::getEngine()
{
    static std::mt19937 engine(std::random_device{}());
    return engine;
}
std::string Generator::generatePassword(std::size_t size)
{
    std::string pass{};
    pass.reserve(size);
    std::size_t index{};
    std::uniform_int_distribution<size_t> dist(0, Pool::asciiPrintablePool.size() - 1);
    for (std::size_t i{}; i < size; ++i)
    {
        index = dist(getEngine());
        pass.push_back(Pool::asciiPrintablePool[index]);
    }
    std::shuffle(pass.begin(), pass.end(), getEngine());
    return pass;
}

[[nodiscard]]std::optional<std::string> Generator::generateByPolicy(PoolType type, PolicyRules ruleSet)
{
    // Build :
    PoolBuilder builder;
    builder.setPool(type);
    // Validation :
    PasswordPolicy policy;
    policy.setPreset(ruleSet);
    // Check :
    PoolCompatibility compact(builder, policy);
    auto [noRep, satis] = compact.validate(ruleSet);
    if (!satis)
    {
        return std::nullopt;
    }
    // Get The result Pool :
    std::string_view finalPool = builder.getPool().pool_;

    // Analyzer For Seperation :
    PoolAnalyzer analyzer(finalPool);
    auto rules = policy.getRules();

    // Generate:
    std::string pass{};
    std::uniform_int_distribution dist(rules.minLength_, rules.maxLength_);
    std::size_t length = dist(Generator::getEngine());
    pass.reserve(length);

    for (std::size_t i{}; i < rules.minLower_; ++i)
    {
        pass += analyzer.pickRandom(Charset::Lower);
    }
    for (std::size_t i{}; i < rules.minUpper_; ++i)
    {
        pass += analyzer.pickRandom(Charset::Upper);
    }
    for (std::size_t i{}; i < rules.minDigit_; ++i)
    {
        pass += analyzer.pickRandom(Charset::Digits);
    }
    for (std::size_t i{}; i < rules.minSymbol_; ++i)
    {
        pass += analyzer.pickRandom(Charset::Symbols);
    }
    std::size_t remain = length -
                         (rules.minLower_ + rules.minUpper_ + rules.minDigit_ + rules.minSymbol_);
    if (remain > 0)
    {
        if (remain <= finalPool.size())
        {
            std::sample(finalPool.begin(),
                        finalPool.end(),
                        std::back_inserter(pass),
                        remain,
                        Generator::getEngine());
        }
        else
        {
            std::uniform_int_distribution<std::size_t> dist(0, finalPool.size() - 1);
            for(std::size_t i{}; i < remain; ++i)
            {
                pass += finalPool[dist(Generator::getEngine())];
            }
        }
    }

    std::shuffle(pass.begin(), pass.end(), Generator::getEngine());
    return pass;
}
