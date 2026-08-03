#pragma once

#include <string>
#include <random>
#include <string_view>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <type_traits>
#include <cstdint>
#include <span>
#include <utility>
#include <concepts>
#include <array>
#include <algorithm>
// MIXING BASED ON THE CHARSET CHOOSING:
enum class Charset
{
    Lower,
    Upper,
    Digits,
    Symbols
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
enum class PoolType : std::uint32_t
{
    None = 0,
    ASCII = 1 << 1,
    HexLower = 1 << 2,
    HexUpper = 1 << 3,
    Binary = 1 << 4,
    Octal = 1 << 5,
    Base32 = 1 << 6,
    Base64 = 1 << 7,
    Base64URL = 1 << 8,
    Vowels = 1 << 9,
    Consonants = 1 << 10,
    All =
        ASCII |
        HexLower |
        HexUpper |
        Binary |
        Octal |
        Base32 |
        Base64 |
        Base64URL |
        Vowels |
        Consonants
};
inline constexpr PoolType DefaultPool =
    static_cast<PoolType>(
        (1u << 0) |
        (1u << 1) |
        (1u << 2) |
        (1u << 3));

// GLOBAL OVERLOADING OF | , & OPERATORS :
[[nodiscard]] constexpr PoolType operator|(PoolType lhs, PoolType rhs) noexcept;
[[nodiscard]] constexpr PoolType operator&(PoolType lhs, PoolType rhs) noexcept;
[[nodiscard]] constexpr PoolType operator|=(PoolType &lhs, PoolType rhs) noexcept;
[[nodiscard]] constexpr PoolType operator&=(PoolType &lhs, PoolType rhs) noexcept;

namespace Pool
{
    // ASCII BASIC POOL:
    inline constexpr std::string_view asciiPrintablePool{
        "abcdefghijklmnopqrstuvwxy"
        "zABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_"
        "=+{}[]:;\"\'><./|~`1234567890"};
    inline constexpr std::string_view vowels{
        "aeiouAEIOU"};
    inline constexpr std::string_view consonants{
        "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"};
    // STANDARD ENCODINGS: Base32(RFC4648) Base64(RFC4648) Base53(URL)
    inline constexpr std::string_view upHexPool{
        "0123456789ABCDEF"},
        lowHexPool{
            "0123456789abcdef"};
    inline constexpr std::string_view octal{"01234567"};
    inline constexpr std::string_view binary{"01"};
    inline constexpr std::string_view Base32Pool{
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"},
        Base64Pool{
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"},
        Base64URL{
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"};

    // WILL ADDING IN FUTURE UPDATES...
    inline constexpr std::string_view emojis{};
    inline constexpr std::string_view greeks{};
    inline constexpr std::string_view specialSymbols{};

    namespace Utilities
    {
        // ADDING A COMPILE-TIME MAKER OF ANY TYPE OF STRINGS :
        inline constexpr auto toCompileTimePool = []<typename T>(const T &input) consteval
            requires std::convertible_to<T, std::string_view>
        {
            return std::string_view(input);
        };
    }
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

    static std::size_t randomIndex(std::span<const std::size_t>);
    void poolChecker();

public:
    explicit PoolAnalyzer(std::string_view);

    [[nodiscard]] std::size_t size() const;

    [[nodiscard]] std::span<const std::size_t>
        getIndices(Charset) const;

    [[nodiscard]] char pickRandom(Charset);

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

    static Policies makePolicy(PolicyRules);

    bool validateManualRules(const Policies &) const;

    Policies currentPolicy_;

    const Policies &passRules() const noexcept { return this->currentPolicy_; }

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

    [[nodiscard]] const Policies &getRules() const noexcept
    {
        return this->passRules();
    };
};

namespace Generator
{
    std::mt19937 &getEngine();

    std::string generateByPolicy(PolicyRules);

    std::string generatePassword(std::size_t);
}
// Making Pool with other defined or custom pool with PoolType

class PoolBuilder
{
private:
    struct PoolEntry
    {
        PoolType type_{};
        std::string pool_{};
    };
    PoolEntry poolProperties_{};
    // TABLE FOR HASFLAG:

    [[nodiscard]] bool processFlags(PoolType flags, const PoolType &type) const noexcept;

public:
    PoolBuilder() = default;
    PoolBuilder(const std::string &pool);

    static const std::array<PoolEntry, 9> poolTable;
    void setCustomPool(const std::string &pool);

    void setPool(const std::string &);
    void setPool(PoolType types);

    const PoolEntry &getPool() const noexcept;
};

class PoolCompatibility
{
public:    
    struct ValidationRules
    {
        bool noRepeat_ = false;
        bool satisPolices_ = false;
        // Relying on Rules of zero ...
    };
    PoolCompatibility() = delete;
    explicit PoolCompatibility(const PoolBuilder &builder, const PasswordPolicy &policies);
    void setPool(const std::string &);

    [[nodiscard]] ValidationRules validate() noexcept;

private:
    ValidationRules checkPair_{};

    PoolBuilder pool_{};
    PasswordPolicy policiesCheck_;

    void deleteDuplications() noexcept;
};