#include "PassForge.hpp"
#include "BruteForce.hpp"
class PassForge
{
public:
    void runPrompt();
private:
    std::string pass_{};
    std::size_t size_{};
    bool SetOPDONE_{false};
    std::string hash_{};
    inline std::string normalize(std::string input)
    {
        std::transform(input.begin(), input.end(), input.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        return input;
    }

    void generateFlow();
    void hashFlow();
    void estimateFlow();
    void crackFlow();
    void saveFlow(); // pass and hash and len this is not for wordlist!
    void setOptions();
};