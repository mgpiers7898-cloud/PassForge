#include "PassForge.hpp"
#include "UnicodeUtils.hpp"
PoolBuilder::PoolBuilder(const std::string &pool) : poolProperties_{{}, pool}
{
}

const std::array<PoolBuilder::PoolEntry, 10> PoolBuilder::poolTable{{{PoolType::ASCII, std::string(Pool::asciiPrintablePool)},
                                                                     {PoolType::Binary, std::string(Pool::binary)},
                                                                     {PoolType::Octal, std::string(Pool::octal)},
                                                                     {PoolType::HexLower, std::string(Pool::lowHexPool)},
                                                                     {PoolType::HexUpper, std::string(Pool::upHexPool)},
                                                                     {PoolType::Base32, std::string(Pool::Base32Pool)},
                                                                     {PoolType::Base64, std::string(Pool::Base64Pool)},
                                                                     {PoolType::Vowels, std::string(Pool::vowels)},
                                                                     {PoolType::Consonants, std::string(Pool::consonants)}}};

void PoolBuilder::setCustomPool(const std::string &pool) { this->poolProperties_.pool_ = pool; }

[[nodiscard]] bool PoolBuilder::processFlags(PoolType flags, const PoolType &type) const noexcept
{
    return (flags & type) == type;
}

void PoolBuilder::setPool(PoolType types)
{
    this->poolProperties_.pool_.clear();
    if ((types & PoolType::Emoji) == PoolType::Emoji)
    {
        for (const auto &it : Translator::emojiPool)
        {
            this->poolProperties_.pool_.append(Translator::toUTF8(it));
        }
    }
    for (const auto &[type, pool] : poolTable)
    {
        if (processFlags(types, type))
        {
            this->poolProperties_.pool_.append(pool);
        }
    }
    this->poolProperties_.type_ = types;
}

void PoolBuilder::setPool(const std::string &pool)
{
    this->poolProperties_.pool_ = pool;
}

const PoolBuilder::PoolEntry &PoolBuilder::getPool() const noexcept
{
    return this->poolProperties_;
}