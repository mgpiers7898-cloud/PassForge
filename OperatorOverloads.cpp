#include"PassForge.hpp"

PoolType operator|(PoolType lhs, PoolType rhs)
{
    auto res = static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs);
    return static_cast<PoolType>(res);
}

PoolType operator|=(PoolType& lhs, PoolType rhs)
{
    unsigned int result =
        static_cast<unsigned int>(lhs) &
        static_cast<unsigned int>(rhs);

    lhs = static_cast<PoolType>(result);
    return lhs;
}

PoolType operator&(PoolType lhs, PoolType rhs)
{
    auto res = static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs);
    return static_cast<PoolType>(res);
}

PoolType operator&=(PoolType& lhs, PoolType rhs)
{
    unsigned int result =
        static_cast<unsigned int>(lhs) &
        static_cast<unsigned int>(rhs);

    lhs = static_cast<PoolType>(result);
    return lhs;
}