#include "PassForge.hpp"
#include <unordered_map>
#include <string>
class PassForge
{
public:
    // A :
    void setPass(const std::string &pass);
    void setOptions(PoolType type, PolicyRules ruleSet);

    // B :
    void runPrompt();
    [[nodiscard]]std::string hash();
    [[nodiscard]]double entropy();
    std::string crackTime(double);
    void saveInFile(const std::string &path = ".PassForge.txt") const;

private:
    std::string pass_{};
    std::size_t size_{};
    inline static const std::unordered_map<std::string, PoolType> poolTypeTable_ =
        {
            {"ascii", PoolType::ASCII},
            {"hexl", PoolType::HexLower},
            {"hexu", PoolType::HexUpper},
            {"bin", PoolType::Binary},
            {"oct", PoolType::Octal},
            {"b32", PoolType::Base32},
            {"b64", PoolType::Base64},
            {"b64u", PoolType::Base64URL},
            {"vow", PoolType::Vowels},
            {"con", PoolType::Consonants},
            {"all", PoolType::All}};
    inline static const std::unordered_map<std::string, PolicyRules> ruleSetTable_ =
        {
            {"toostrong", PolicyRules::TooStrong},
            {"strong", PolicyRules::Strong},
            {"medium", PolicyRules::Medium},
            {"simple", PolicyRules::Simple}};

    std::string normalize(std::string input)
    {
        std::transform(input.begin(), input.end(), input.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        return input;
    }

    bool checkPass()
    {
        return this->pass_.empty();
    }
};