#include "PassForge.hpp"

// Engines :
[[nodiscard]] std::size_t PoolAnalyzer::randomIndex(std::span<const std::size_t> list)
{
    if (list.empty())
        throw std::runtime_error("\nEMPTY CHARSET!\n");
    auto engine(Generator::getEngine());
    std::uniform_int_distribution<std::size_t> dist(0, list.size() - 1);
    return dist(engine);
}

void PoolAnalyzer::AnalyzeResults::reset() noexcept
{
    AnalyzeResults::lowerIndices_.clear();
    AnalyzeResults::upperIndices_.clear();
    AnalyzeResults::digitIndices_.clear();
    AnalyzeResults::symbolIndices_.clear();
}

void PoolAnalyzer::poolChecker()
{
    counts_.reset();
    for (std::size_t i{}; i < pool_.size(); ++i)
    {
        if (std::islower(static_cast<unsigned char>(pool_[i])))
        {
            counts_.lowerIndices_.push_back(i);
        }
        else if (std::isupper(static_cast<unsigned char>(pool_[i])))
        {
            counts_.upperIndices_.push_back(i);
        }
        else if (std::isdigit(static_cast<unsigned char>(pool_[i])))
        {
            counts_.digitIndices_.push_back(i);
        }
        else if (std::ispunct(static_cast<unsigned char>(pool_[i])))
        {
            counts_.symbolIndices_.push_back(i);
        }
    }
}

PoolAnalyzer::PoolAnalyzer(std::string_view pool) : pool_(pool) { poolChecker(); }

// ASCII BASE ================================================================
[[nodiscard]] std::size_t PoolAnalyzer::size() const
{
    return this->pool_.size();
}

[[nodiscard]] std::span<const std::size_t>
PoolAnalyzer::getIndices(Charset type) const
{
    switch (type)
    {
    case Charset::Lower:
        return counts_.lowerIndices_;
    case Charset::Upper:
        return counts_.upperIndices_;
    case Charset::Digits:
        return counts_.digitIndices_;
    case Charset::Symbols:
        return counts_.symbolIndices_;
    }
    // add something for : these :
    // Excluded and Ambigiuous and Emoji character will implement in the near future!
    std::unreachable();
}

[[nodiscard]]char PoolAnalyzer::pickRandom(Charset type)
{
    auto indices = getIndices(type);
    auto randomPos = randomIndex(indices);
    std::size_t realIndex = indices[randomPos];

    return pool_[realIndex];
}
//============================================================================
void PoolAnalyzer::setPool(std::string_view customPool) noexcept
{
    pool_ = customPool;
    poolChecker();
}
