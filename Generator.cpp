#include "PassForge.hpp"

std::mt19937 &Generator::getEngine()
{
    static std::mt19937 engine(std::random_device{}());
    return engine;
}
std::string Generator::lowerAlphaWithNums(std::size_t size)
{
    std::string pass{};
    CharacterAnalyzer charset(Pool::charsetsPool);

    std::size_t order{2};

    std::uniform_int_distribution<std::size_t> dist(0, order - 1);
    std::size_t rand{};
    for (std::size_t it = 0; it < size; it++)
    {
        rand = dist(Generator::getEngine());
        if (rand == 1)
        {
            pass.push_back(charset.getOneRandomizeChar(Charset::Alpha));
        }
        else if (rand == 0)
        {
            pass.push_back(charset.getOneRandomizeChar(Charset::Digit));
        }
    }
    return pass;
}
std::string Generator::mixPasscode(std::size_t size)
{
    std::string pass{};

    std::uniform_int_distribution<std::size_t> dist(0, 3);
    std::size_t randType{};

    CharacterAnalyzer charset(Pool::charsetsPool);
    for (std::size_t i = 0; i < size; i++)
    {
        randType = dist(Generator::getEngine());

        switch (randType)
        {
        case 0:
            pass.push_back(charset.getOneRandomizeChar(Charset::Alpha));
            break;
        case 1:
            pass.push_back(charset.getOneRandomizeChar(Charset::CapAlpha));
            break;
        case 2:
            pass.push_back(charset.getOneRandomizeChar(Charset::Digit));
            break;
        case 3:
            pass.push_back(charset.getOneRandomizeChar(Charset::Symbol));
            break;
        default:
            pass.push_back(charset.getOneRandomizeChar(Charset::Alpha));
        }
    }
    return pass;
}