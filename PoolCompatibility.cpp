#include "PassForge.hpp"
PoolCompatibility::PoolCompatibility(PoolBuilder &pool, const PasswordPolicy &policies) : pool_(pool), policiesCheck_(policies)
{
}

void PoolCompatibility::deleteDuplications() noexcept
{
    auto& pool = this->pool_.getThePool();
    //sorting
    std::sort(pool.begin(), pool.end());
    // Make Unique
    std::string::iterator newPoolIter = 
        std::unique(pool.begin(), pool.end());

    // Applying The unique
    pool.erase(newPoolIter, pool.end());


    std::shuffle(pool.begin(), pool.end(), Engine::getEngine());
    this->pool_.setPool(pool);
}

[[nodiscard]]PoolCompatibility::ValidationRules PoolCompatibility::validate(PolicyRules rules)
{
    // first del the duplications : 
    std::size_t fSize = this->pool_.getPool().pool_.size();
    deleteDuplications();
    std::size_t aSize = this->pool_.getPool().pool_.size();
    this->checkPair_.noRepeat_ = (fSize != aSize);

    checkPair_.originalSize_ = fSize;
    checkPair_.dedupedSize_ = aSize;

    this->policiesCheck_.setPreset(rules);
    const std::string& passingPool = this->pool_.getPool().pool_;
    PoolAnalyzer analyzer(passingPool);
    
    this->checkPair_.satisPolices_ =
        this->policiesCheck_.isSatisfiedBy(analyzer, aSize);

    return this->checkPair_;
}

void PoolCompatibility::setPool(const std::string& pool)
{
    this->pool_.setPool(pool);
}