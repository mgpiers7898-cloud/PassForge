#include "PassForge.hpp"

PoolCompatibility::PoolCompatibility(const PoolBuilder &pool, const PasswordPolicy &policies) : pool_(pool), policiesCheck_(policies)
{
}

void PoolCompatibility::deleteDuplications() noexcept
{
    //sorting
    std::string pool = this->pool_.getPool().pool_;
    std::sort(pool.begin(), pool.end());
    // Make Unique
    std::string::iterator newPoolIter = 
        std::unique(pool.begin(), pool.end());
    // Applying The unique
    pool.resize(std::distance(pool.begin(), newPoolIter));

    this->pool_.setPool(pool);
}

[[nodiscard]] PoolCompatibility::ValidationRules PoolCompatibility::validate()
    noexcept
{
    // first del the duplications : 
    std::size_t fSize = this->pool_.getPool().pool_.size();
    deleteDuplications();
    std::size_t aSize = this->pool_.getPool().pool_.size();
    this->checkPair_.noRepeat_ = (fSize != aSize);

    this->policiesCheck_.setPreset(PolicyRules::Strong);// default for NOW!
    // we will make a generator able to pass for now its default...
    
}