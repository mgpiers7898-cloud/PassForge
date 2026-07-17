#include "PassForge.hpp"

std::mt19937 &Generator::getEngine()
{
    static std::mt19937 engine(std::random_device{}());
    return engine;
}
std::string Generator::lowerAlphaWithNums(std::size_t size)
{
    std::string pass{};
    CharacterAnalyzer charset(Pool::asciiPrintablePool);

    std::size_t order{2};

    std::uniform_int_distribution<std::size_t> dist(0, order - 1);
    std::size_t rand{};
    for (std::size_t it = 0; it < size; it++)
    {
        rand = dist(Generator::getEngine());
        if (rand == 1)
        {
            pass.push_back(charset.getOneRandomizeChar(Charset::Lower));
        }
        else if (rand == 0)
        {
            pass.push_back(charset.getOneRandomizeChar(Charset::Digits));
        }
    }
    return pass;
}
std::string Generator::mixPasscode(std::size_t size)
{
    std::string pass{};

    std::uniform_int_distribution<std::size_t> dist(0, 3);
    std::size_t randType{};

    CharacterAnalyzer charset(Pool::asciiPrintablePool);
    for (std::size_t i = 0; i < size; i++)
    {
        randType = dist(Generator::getEngine());

        switch (randType)
        {
        case 0:
            pass.push_back(charset.getOneRandomizeChar(Charset::Lower));
            break;
        case 1:
            pass.push_back(charset.getOneRandomizeChar(Charset::Upper));
            break;
        case 2:
            pass.push_back(charset.getOneRandomizeChar(Charset::Digits));
            break;
        case 3:
            pass.push_back(charset.getOneRandomizeChar(Charset::Symbols));
            break;
        default:
            pass.push_back(charset.getOneRandomizeChar(Charset::Lower));
        }
    }
    return pass;
}
std::string Generator::policyBasedPasscode(PolicyRules ruleSet)
{
    std::string pass{};
    CharacterAnalyzer charset(Pool::asciiPrintablePool);
    
    PasswordPolicy rules;
    rules.setPreset(ruleSet);
    
    auto currentRule = rules.getRules();

    //C++17 required for this binding :
    auto [minLen, maxLen, low, up, dig, sym, exclude, emoji] = currentRule;
    std::size_t required{low + up + sym + dig};
    std::uniform_int_distribution<std::size_t> dist(minLen, maxLen);

    std::size_t length{dist(getEngine())};
    std::size_t remaining{length - required};

    for(std::size_t it = 0; it < low; it++)
    {
        pass.push_back(charset.getOneRandomizeChar(Charset::Lower));
    }
    for(std::size_t it = 0; it < up; it++)
    {
        pass.push_back(charset.getOneRandomizeChar(Charset::Upper));
    }
    for(std::size_t it = 0; it < dig; it++)
    {
        pass.push_back(charset.getOneRandomizeChar(Charset::Digits));
    }
    for(std::size_t it = 0; it < sym; it++)
    {
        pass.push_back(charset.getOneRandomizeChar(Charset::Symbols));
    }
    // add something for : these : 
    // Excluded and Ambigiuous and Emoji character will implement in the near future!
    pass.append(mixPasscode(remaining));

    return pass;
}

std::string Generator::multiPoolPasscode(
    std::size_t size = 20, PoolType type)
{
    
}