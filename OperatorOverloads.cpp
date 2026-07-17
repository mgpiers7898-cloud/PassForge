#include"PassForge.hpp"

constexpr PoolType operator|(PoolType lhs, PoolType rhs)
{
    auto res = static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs);
    return static_cast<PoolType>(res);
}

constexpr PoolType operator|=(PoolType& lhs, PoolType rhs)
{
    unsigned int result = 
    static_cast<PoolBits>(lhs) &
    static_cast<PoolBits>(rhs);

    lhs = static_cast<PoolType>(result);
    return lhs;
}

constexpr PoolType operator&(PoolType lhs, PoolType rhs)
{
    auto res = static_cast<PoolBits>(lhs) & static_cast<PoolBits>(rhs);
    return static_cast<PoolType>(res);
}

constexpr PoolType operator&=(PoolType& lhs, PoolType rhs)
{
    unsigned int result =
    static_cast<PoolBits>(lhs) &
    static_cast<PoolBits>(rhs);

    lhs = static_cast<PoolType>(result);
    return lhs;
}