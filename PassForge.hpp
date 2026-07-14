#pragma once

#include <string>
#include <random>
#include <string_view>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <cstddef>
// MIXING BASED ON THE CHARSET CHOOSING:
enum class Charset
{
    Alpha,
    CapAlpha,
    Digit,
    Symbol
};

// Password Policy Scoped enum:
enum class PolicyRules
{
    TooStrong,
    Strong,
    Medium,
    Simple
};

namespace Pool
{
    inline constexpr std::string_view charsetsPool{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+{}[]:;\"\'><./|~`1234567890"};
    inline constexpr std::string_view hexPool{};
    inline constexpr std::string_view emojis{};
    inline constexpr std::string_view greeks{};
    inline constexpr std::string_view specialSymbols{};
}

class CharacterAnalyzer
{
private:
    struct AnalyzeResults
    {
        std::vector<std::size_t> lowerIndices_;
        std::vector<std::size_t> upperIndices_;
        std::vector<std::size_t> digitIndices_;
        std::vector<std::size_t> symbolIndices_;

        void reset() noexcept;
    };

    std::string_view pool_;
    AnalyzeResults counts_;

    std::size_t randomIndex(const std::vector<std::size_t> &);
    void analyze();
    constexpr unsigned short charsetSize() const;

public:
    CharacterAnalyzer(std::string_view);

    std::size_t size(Charset) const;

    const std::vector<std::size_t> &
        getIndices(Charset) const;

    char getOneRandomizeChar(Charset);

    void setPool(std::string_view) noexcept;
};

class PasswordPolicy
{
private:
    struct Policies
    {
        std::size_t minLength_;
        std::size_t maxLength_;
        std::size_t minLower_;
        std::size_t minUpper_;
        std::size_t minDigit_;
        std::size_t minSymbol_;
        bool excludeAmbiguous_;
        bool allowEmojis_;

        Policies();
        Policies(std::size_t,
                 std::size_t,
                 std::size_t,
                 std::size_t,
                 std::size_t,
                 std::size_t,
                 bool,
                 bool);
    };

    Policies makePolicy(PolicyRules);

    bool validateManualRules(const Policies &) const;

    Policies currentPolicy_;

    static constexpr const char *validationMessage =
        R"(Manual policy requirements:
    - Minimum length must not exceed maximum length.
    - Minimum lowercase count must fit within the minimum length.
    - Minimum uppercase count must fit within the minimum length.
    - Minimum digit count must fit within the minimum length.
    - The sum of required character categories must not exceed the minimum length.)";

public:
    void setPreset(PolicyRules);

    void setManually(std::size_t min, std::size_t max, std::size_t lowers,
                     std::size_t uppers, std::size_t digits, std::size_t sym, bool ambigiuous, bool emoji);
};

namespace Generator
{
    std::mt19937 &getEngine();

    std::string lowerAlphaWithNums(std::size_t);

    std::string mixPasscode(std::size_t);
}