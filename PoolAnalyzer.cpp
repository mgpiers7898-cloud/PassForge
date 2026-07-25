#include "PassForge.hpp"

// Engines :
std::size_t PoolAnalyzer::randomIndex(const std::vector<std::size_t>& list)
{
    static std::mt19937 engine(std::random_device{}());
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
constexpr std::size_t PoolAnalyzer::charsetSize() const { return pool_.size(); }

PoolAnalyzer::PoolAnalyzer(std::string_view pool) : pool_(pool) { poolChecker(); }

std::size_t PoolAnalyzer::size(Charset type) const
{
    switch (type)
    {
    case Charset::Lower:
        return this->counts_.lowerIndices_.size();
    case Charset::Upper:
        return this->counts_.upperIndices_.size();
    case Charset::Digits:
        return this->counts_.digitIndices_.size();
    case Charset::Symbols:
        return this->counts_.symbolIndices_.size();
    default:
        return this->charsetSize();
    }
}
const std::vector<std::size_t>& PoolAnalyzer::getIndices(Charset type) const
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
    throw std::invalid_argument("\nINVALID CHARSET!\n");
}

char PoolAnalyzer::getOneRandomizeChar(Charset type)
{
    const auto& indices = getIndices(type);
    std::size_t randomPos = randomIndex(indices);
    std::size_t realIndex = indices[randomPos];

    return pool_[realIndex];
}

void PoolAnalyzer::setPool(std::string_view customPool) noexcept
{
    pool_ = customPool;
    poolChecker();
}

std::vector<std::size_t> PoolAnalyzer::listPasser(PoolType types) const
{
    std::vector<std::size_t> charsetIndices{};
    if ((types & PoolType::All) != PoolType::None)
    {
        for (std::size_t it = 0; it < Pool::asciiPrintablePool.size(); it++)
        {
            charsetIndices.push_back(it);
        }
        return charsetIndices;
    }
    if ((types & PoolType::Lower) != PoolType::None)
    {
        const auto& tempList = PoolAnalyzer::getIndices(Charset::Lower);
        for (std::size_t it : tempList)
        {
            charsetIndices.push_back(it);
        }
    }
    if ((types & PoolType::Upper) != PoolType::None)
    {
        const auto& tempList = PoolAnalyzer::getIndices(Charset::Upper);
        for (std::size_t it : tempList)
        {
            charsetIndices.push_back(it);
        }
    }
    if ((types & PoolType::Digits) != PoolType::None)
    {
        const auto& tempList = PoolAnalyzer::getIndices(Charset::Digits);
        for (std::size_t it : tempList)
        {
            charsetIndices.push_back(it);
        }
    }
    if ((types & PoolType::Symbols) != PoolType::None)
    {
        const auto& tempList = PoolAnalyzer::getIndices(Charset::Symbols);
        for (std::size_t it : tempList)
        {
            charsetIndices.push_back(it);
        }
    }
    return charsetIndices;
}


