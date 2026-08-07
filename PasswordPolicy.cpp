#include "PassForge.hpp"

// PASSWORD POLICY :
PasswordPolicy::Policies::Policies() = default;
PasswordPolicy::Policies::Policies(std::size_t min, std::size_t max, std::size_t lowers,
                                   std::size_t uppers, std::size_t digits, std::size_t symbols,
                                   bool ambigiuous, bool emoji) : minLength_(min), maxLength_(max), minLower_(lowers), minUpper_(uppers),
                                                                  minDigit_(digits), minSymbol_(symbols), excludeAmbiguous_(ambigiuous), allowEmojis_(emoji)
{
}

PasswordPolicy::Policies PasswordPolicy::makePolicy(PolicyRules requirement)
{
    switch (requirement)
    {
    case PolicyRules::TooStrong:
        return Policies(24, 40, 5, 5, 5, 5, false, false);
    case PolicyRules::Strong:
        return Policies(16, 26, 3, 3, 3, 3, false, false);
    case PolicyRules::Medium:
        return Policies(12, 16, 2, 2, 2, 2, true, false);
    case PolicyRules::Simple:
        return Policies(8, 12, 1, 1, 1, 1, true, false);
    default:
        throw std::invalid_argument("\nSPECIFY THE RIGHT RULE SET!\n");
    }
}

bool PasswordPolicy::validateManualRules(const PasswordPolicy::Policies &p) const
{ // the Reduandant is for advanced Error checking in future!
    return p.minLength_ >= 8 &&
           p.minLength_ <= p.maxLength_ &&
           p.minLower_ <= p.minLength_ &&
           p.minUpper_ <= p.minLength_ &&
           p.minDigit_ <= p.minLength_ &&
           p.minSymbol_ <= p.minLength_ &&
           (p.minLower_ + p.minUpper_ + p.minDigit_ + p.minSymbol_) <= p.minLength_ && p.maxLength_ <= 256;
}

void PasswordPolicy::setManually(std::size_t min, std::size_t max, std::size_t lowers,
                                 std::size_t uppers, std::size_t digits, std::size_t sym, bool ambigiuous, bool emoji)
{
    auto newPolicy = Policies(min, max, lowers, uppers, digits, sym, ambigiuous, emoji);
    if (this->validateManualRules(newPolicy))
    {
        currentPolicy_ = newPolicy;
    }
    else
    {
        throw std::invalid_argument(this->validationMessage);
    }
}

void PasswordPolicy::setPreset(PolicyRules power)
{
    currentPolicy_ = makePolicy(power);
}

bool PasswordPolicy::isSatisfiedBy(const PoolAnalyzer &analyzer, std::size_t actualSize) const
{
    const auto &low = analyzer.getIndices(Charset::Lower);
    const auto &upp = analyzer.getIndices(Charset::Upper);
    const auto &dig = analyzer.getIndices(Charset::Digits);
    const auto &sym = analyzer.getIndices(Charset::Symbols); 

    if (actualSize >= this->currentPolicy_.minLength_ &&
        low.size() >= this->currentPolicy_.minLower_ &&
        upp.size() >= this->currentPolicy_.minUpper_ &&
        dig.size() >= this->currentPolicy_.minDigit_ &&
        sym.size() >= this->currentPolicy_.minSymbol_)
    {
        return true;
    }
    return false;
}