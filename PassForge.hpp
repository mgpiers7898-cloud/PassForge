#pragma once

#include <string>
#include <random>
#include <string_view>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <type_traits>
#include <iostream> // for testing and see the result
// MIXING BASED ON THE CHARSET CHOOSING:
enum class Charset
{
    Lower,
    Upper,
    Digits,
    Symbols,
    HexLower,
    HexUpper,
    Binary,
    Octal,
    Base32,
    Base64,
    Vowels,
    Consonants
};

// Password Policy Scoped enum:
enum class PolicyRules
{
    TooStrong,
    Strong,
    Medium,
    Simple
};

// MIXING SEVERAL ENUM AND PASSING TO THE APPROPRIATE GENERATOR:
enum class PoolType : unsigned int
{
    None = 0,
    Lower = 1 << 0,
    Upper = 1 << 1,
    Digits = 1 << 2,
    Symbols = 1 << 3,
    HexLower = 1 << 4,
    HexUpper = 1 << 5,
    Binary = 1 << 6,
    Octal = 1 << 7,
    Base32 = 1 << 8,
    Base64 = 1 << 9,
    Vowels = 1 << 10,
    Consonants = 1 << 11,
    All = 1 << 12,
};
inline constexpr PoolType DefaultPool =
static_cast<PoolType>(
    (1u << 0) |
    (1u << 1) |
    (1u << 2) |
    (1u << 3));

// GLOBAL OVERLOADING OF | , & OPERATORS :
PoolType operator|(PoolType lhs, PoolType rhs);
PoolType operator&(PoolType lhs, PoolType rhs);
PoolType operator|=(PoolType& lhs, PoolType rhs);
PoolType operator&=(PoolType& lhs, PoolType rhs);

namespace Pool
{
    // ASCII BASIC POOL:
    inline constexpr std::string_view asciiPrintablePool{
        "abcdefghijklmnopqrstuvwxy"
        "zABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_"
        "=+{}[]:;\"\'><./|~`1234567890"
    };
    inline constexpr std::string_view vowels{
        "aeiouAEIOU"
    };
    inline constexpr std::string_view consonants{
        "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"
    };
    // STANDARD ENCODINGS: Base32(RFC4648) Base64(RFC4648) Base53(URL)
    inline constexpr std::string_view upHexPool{
        "0123456789ABCDEF" },
        lowHexPool{
        "0123456789abcdef"
    };
    inline constexpr std::string_view octal{ "01234567" };
    inline constexpr std::string_view binary{ "01" };
    inline constexpr std::string_view Base32Pool{
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567" },
        Base64Pool{
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" },
            Base64URL{
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_" };

    // WILL ADDING IN FUTURE UPDATES...
    inline constexpr std::string_view emojis{};
    inline constexpr std::string_view greeks{};
    inline constexpr std::string_view specialSymbols{};
}

class PoolAnalyzer
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

    std::size_t randomIndex(const std::vector<std::size_t>&);
    void poolChecker();
    constexpr std::size_t charsetSize() const;

public:
    PoolAnalyzer(std::string_view);

    std::size_t size(Charset) const;

    const std::vector<std::size_t>&
        getIndices(Charset) const;


    char getOneRandomizeChar(Charset);

    void setPool(std::string_view) noexcept;
    void setMixPool(PoolType) noexcept;

    std::vector<std::size_t> listPasser(PoolType) const;
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

    bool validateManualRules(const Policies&) const;

    Policies currentPolicy_;

    const Policies& passRules() const noexcept { return this->currentPolicy_; }

    static constexpr const char* validationMessage =
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

    const Policies& getRules() const
    {
        return this->passRules();
    };
};

namespace Generator
{
    std::mt19937& getEngine();

    std::string lowerAlphaWithNums(std::size_t);

    std::string mixPasscode(std::size_t);

    std::string policyBasedPasscode(PolicyRules rule);

    /*std::string multiPoolPasscode(
        std::size_t size = static_cast<std::size_t>(PolicyRules::Strong), PoolType);*/
}