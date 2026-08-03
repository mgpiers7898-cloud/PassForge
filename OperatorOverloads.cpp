#include"PassForge.hpp"

[[nodiscard]]constexpr PoolType operator|(PoolType lhs, PoolType rhs) noexcept
{
    auto res = static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs);
    return static_cast<PoolType>(res);
}

[[nodiscard]]constexpr PoolType operator|=(PoolType& lhs, PoolType rhs) noexcept
{
    unsigned int result =
        static_cast<unsigned int>(lhs) |
        static_cast<unsigned int>(rhs);

    lhs = static_cast<PoolType>(result);
    return lhs;
}

[[nodiscard]]constexpr PoolType operator&(PoolType lhs, PoolType rhs) noexcept
{
    auto res = static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs);
    return static_cast<PoolType>(res);
}

[[nodiscard]]constexpr PoolType operator&=(PoolType& lhs, PoolType rhs) noexcept
{
    unsigned int result =
        static_cast<unsigned int>(lhs) &
        static_cast<unsigned int>(rhs);

    lhs = static_cast<PoolType>(result);
    return lhs;
}