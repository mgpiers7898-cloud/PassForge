#include "PassForge.hpp"

std::mt19937 &Generator::getEngine()
{
    static std::mt19937 engine(std::random_device{}());
    return engine;
}

std::string Generator::generateByPolicy(PolicyRules ruleSet)
{
    std::string pass{};
    PoolAnalyzer charset(Pool::asciiPrintablePool);

    PasswordPolicy rules;
    rules.setPreset(ruleSet);
    const auto &currentRule = rules.getRules();
    auto [minLen, maxLen, low, up, dig, sym, exclude, emoji] = currentRule;
    std::size_t required{low + up + sym + dig};

    std::uniform_int_distribution<std::size_t> dist(minLen, maxLen);
    std::size_t length{dist(getEngine())};
    pass.reserve(length);

    

    // C++17 required for this binding :

    std::size_t remaining{length - required};

    for (std::size_t it = 0; it < low; it++)
    {
        pass.push_back(charset.pickRandom(Charset::Lower));
    }
    for (std::size_t it = 0; it < up; it++)
    {
        pass.push_back(charset.pickRandom(Charset::Upper));
    }
    for (std::size_t it = 0; it < dig; it++)
    {
        pass.push_back(charset.pickRandom(Charset::Digits));
    }
    for (std::size_t it = 0; it < sym; it++)
    {
        pass.push_back(charset.pickRandom(Charset::Symbols));
    }
    // add something for : these :
    // Excluded and Ambigiuous and Emoji character will implement in the near future!
    if (remaining > 0)
    {
        size_t rand{};
        std::uniform_int_distribution<std::size_t>
            distribution(0, Pool::asciiPrintablePool.size() - 1);
        for (size_t i{}; i < remaining; ++i)
        {
            rand = distribution(getEngine());
            pass.push_back(Pool::asciiPrintablePool[rand]);
        }
    }
    std::shuffle(pass.begin(), pass.end(), getEngine());
    return pass;
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
