#include"PassForge.hpp"
#include <unordered_map>
#include <string>
class PassForge
{
public:
    // A :
    void setPass(const std::string& pass);
    void setOptions(PoolType type, PolicyRules ruleSet);

    // B :
    void runPrompt();
    std::string hash();
    double entropy();
    std::string crackTime();
    void print();
    void save();

private:
    std::string pass_{};
    inline static const std::unordered_map<std::string, PoolType> poolTypeTable_ =
    {
        {"ascii", PoolType::ASCII},
        {"hexl", PoolType::HexLower},
        {"hexu", PoolType::HexUpper},
        {"bin", PoolType::Binary},
        {"Oct", PoolType::Octal},
        {"b32", PoolType::Base32},
        {"b64", PoolType::Base64},
        {"b64u", PoolType::Base64URL},
        {"Vow", PoolType::Vowels},
        {"Con", PoolType::Consonants},
        {"all", PoolType::All}
    };
    inline static const std::unordered_map<std::string, PolicyRules> ruleSetTable_ = 
    {
        {"toostrong", PolicyRules::TooStrong},
        {"strong", PolicyRules::Strong},
        {"medium", PolicyRules::Medium},
        {"simple", PolicyRules::Simple}
    };
    
    std::string normalize(std::string input)
    {
        std::transform(input.begin(), input.end(), input.begin(),
            [](unsigned char c){return std::tolower(c);});
        return input;
    }

    bool checkPass()
    {
        return this->pass_.empty();
    }
};