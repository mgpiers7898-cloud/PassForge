#include "PassForge.hpp"

void CharacterAnalyzer::AnalyzeResults::reset() noexcept {}

// Engines :
std::size_t CharacterAnalyzer::randomIndex(const std::vector<std::size_t> &list)
{
    static std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, list.size() - 1);
    return dist(engine);
}

void CharacterAnalyzer::analyze()
{
    for (std::size_t it = 0; it < pool_.size(); it++)
    {
        if (std::islower(static_cast<unsigned char>(pool_[it])))
        {
            counts_.lowerIndices_.push_back(it);
        }
        else if (std::isupper(static_cast<unsigned char>(pool_[it])))
        {
            counts_.upperIndices_.push_back(it);
        }
        else if (std::isdigit(static_cast<unsigned char>(pool_[it])))
        {
            counts_.digitIndices_.push_back(it);
        }
        else if (std::ispunct(static_cast<unsigned char>(pool_[it])))
        {
            counts_.symbolIndices_.push_back(it);
        }
    }
}
constexpr unsigned short CharacterAnalyzer::charsetSize() const { return pool_.size(); }

CharacterAnalyzer::CharacterAnalyzer(std::string_view pool) : pool_(pool) { analyze(); }

std::size_t CharacterAnalyzer::size(Charset type) const
{
    switch (type)
    {
    case Charset::Alpha:
        return this->counts_.lowerIndices_.size();
    case Charset::CapAlpha:
        return this->counts_.upperIndices_.size();
    case Charset::Digit:
        return this->counts_.digitIndices_.size();
    case Charset::Symbol:
        return this->counts_.symbolIndices_.size();
    default:
        return this->charsetSize();
    }
}
const std::vector<std::size_t> &CharacterAnalyzer::getIndices(Charset type) const
{
    switch (type)
    {
    case Charset::Alpha:
        return counts_.lowerIndices_;
    case Charset::CapAlpha:
        return counts_.upperIndices_;
    case Charset::Digit:
        return counts_.digitIndices_;
    case Charset::Symbol:
        return counts_.symbolIndices_;
    }
    throw std::invalid_argument("\nINVALID CHARSET!\n");
}

char CharacterAnalyzer::getOneRandomizeChar(Charset type)
{
    const auto &indices = getIndices(type);
    std::size_t randomPos = randomIndex(indices);
    std::size_t realIndex = indices[randomPos];

    return pool_[realIndex];
}

void CharacterAnalyzer::setPool(std::string_view customPool) noexcept
{
    pool_ = customPool;
    analyze();
}