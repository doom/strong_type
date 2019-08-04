/*
** Created by doom on 26/10/18.
*/

#ifndef STRONG_TYPE_TRAITS_HPP
#define STRONG_TYPE_TRAITS_HPP

#include <st/unwrap.hpp>

namespace st
{
    namespace traits
    {
        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct addable
        {
            friend constexpr ReturnT operator+(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return ReturnT(lhs.value() + unwrap(rhs));
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr ReturnT operator+(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return ReturnT(unwrap(lhs) + rhs.value());
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct subtractable
        {
            friend constexpr ReturnT operator-(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return ReturnT(lhs.value() - unwrap(rhs));
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct multiplicable
        {
            friend constexpr ReturnT operator*(const T &lhs, const OtherOperandT &other) noexcept
            {
                return ReturnT(lhs.value() * unwrap(other));
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr ReturnT operator*(const OtherOperandT &other, const T &lhs) noexcept
            {
                return ReturnT(unwrap(other) * lhs.value());
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct dividable
        {
            friend constexpr ReturnT operator/(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return ReturnT(lhs.value() / unwrap(rhs));
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct modulable
        {
            friend constexpr ReturnT operator%(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return ReturnT(lhs.value() % unwrap(rhs));
            }
        };

        template <typename T>
        struct incrementable
        {
            friend constexpr T &operator++(T &t) noexcept
            {
                ++t.value();
                return t;
            }

            friend constexpr const T operator++(T &t, int) noexcept
            {
                T ret(t);

                ++t.value();
                return ret;
            }
        };

        template <typename T>
        struct decrementable
        {
            friend constexpr T &operator--(T &t) noexcept
            {
                --t.value();
                return t;
            }

            friend constexpr const T operator--(T &t, int) noexcept
            {
                T ret(t);

                --t.value();
                return ret;
            }
        };

        template <typename T, typename OtherOperandT = T>
        struct equality_comparable
        {
            friend constexpr bool operator==(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return lhs.value() == unwrap(rhs);
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr bool operator==(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return unwrap(lhs) == rhs.value();
            }

            friend constexpr bool operator!=(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return lhs.value() != unwrap(rhs);
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr bool operator!=(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return unwrap(lhs) != rhs.value();
            }
        };

        template <typename T, typename OtherOperandT = T>
        struct orderable
        {
            friend constexpr bool operator<(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return lhs.value() < unwrap(rhs);
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr bool operator<(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return unwrap(lhs) < rhs.value();
            }

            friend constexpr bool operator<=(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return lhs.value() <= unwrap(rhs);
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr bool operator<=(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return unwrap(lhs) <= rhs.value();
            }

            friend constexpr bool operator>(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return lhs.value() > unwrap(rhs);
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr bool operator>(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return unwrap(lhs) > rhs.value();
            }

            friend constexpr bool operator>=(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return lhs.value() >= unwrap(rhs);
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr bool operator>=(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return unwrap(lhs) >= rhs.value();
            }
        };

        template <typename T>
        struct arithmetic : addable<T>,
                            subtractable<T>,
                            multiplicable<T>,
                            dividable<T>,
                            modulable<T>,
                            incrementable<T>,
                            decrementable<T>,
                            equality_comparable<T>,
                            orderable<T>
        {
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct bitwise_orable
        {
            friend constexpr ReturnT operator|(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return ReturnT(lhs.value() | unwrap(rhs));
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr ReturnT operator|(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return ReturnT(unwrap(lhs) | rhs.value());
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct bitwise_andable
        {
            friend constexpr ReturnT operator&(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return ReturnT(lhs.value() & unwrap(rhs));
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr ReturnT operator&(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return ReturnT(unwrap(lhs) & rhs.value());
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct bitwise_xorable
        {
            friend constexpr ReturnT operator^(const T &lhs, const OtherOperandT &rhs) noexcept
            {
                return ReturnT(lhs.value() ^ unwrap(rhs));
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr ReturnT operator^(const OtherOperandT &lhs, const T &rhs) noexcept
            {
                return ReturnT(unwrap(lhs) ^ rhs.value());
            }
        };

        template <typename T, typename ReturnT = T>
        struct bitwise_negatable
        {
            friend constexpr ReturnT operator~(const T &lhs) noexcept
            {
                return ReturnT(~lhs.value());
            }
        };

        template <typename T>
        struct bitwise_manipulable : bitwise_orable<T>,
                                     bitwise_andable<T>,
                                     bitwise_xorable<T>,
                                     bitwise_negatable<T>
        {
        };
    }

    struct addable
    {
        template <typename T>
        using type = traits::addable<T>;
    };

    template <typename OtherOperandT>
    struct addable_with
    {
        template <typename T>
        using type = traits::addable<T, OtherOperandT>;
    };

    struct subtractable
    {
        template <typename T>
        using type = traits::subtractable<T>;
    };

    template <typename ReturnT>
    struct subtractable_to
    {
        template <typename T>
        using type = traits::subtractable<T, T, ReturnT>;
    };

    struct multiplicable
    {
        template <typename T>
        using type = traits::multiplicable<T>;
    };

    template <typename OtherOperandT>
    struct multiplicable_with
    {
        template <typename T>
        using type = traits::multiplicable<T, OtherOperandT>;
    };

    struct dividable
    {
        template <typename T>
        using type = traits::dividable<T>;
    };

    struct modulable
    {
        template <typename T>
        using type = traits::modulable<T>;
    };

    struct incrementable
    {
        template <typename T>
        using type = traits::incrementable<T>;
    };

    struct decrementable
    {
        template <typename T>
        using type = traits::decrementable<T>;
    };

    struct equality_comparable
    {
        template <typename T>
        using type = traits::equality_comparable<T>;
    };

    struct orderable
    {
        template <typename T>
        using type = traits::orderable<T>;
    };

    struct arithmetic
    {
        template <typename T>
        using type = traits::arithmetic<T>;
    };

    struct bitwise_orable
    {
        template <typename T>
        using type = traits::bitwise_orable<T>;
    };

    template <typename OtherOperandT>
    struct bitwise_orable_with
    {
        template <typename T>
        using type = traits::bitwise_orable<T, OtherOperandT>;
    };

    struct bitwise_andable
    {
        template <typename T>
        using type = traits::bitwise_andable<T>;
    };

    template <typename OtherOperandT>
    struct bitwise_andable_with
    {
        template <typename T>
        using type = traits::bitwise_andable<T, OtherOperandT>;
    };

    struct bitwise_xorable
    {
        template <typename T>
        using type = traits::bitwise_xorable<T>;
    };

    template <typename OtherOperandT>
    struct bitwise_xorable_with
    {
        template <typename T>
        using type = traits::bitwise_xorable<T, OtherOperandT>;
    };

    struct bitwise_negatable
    {
        template <typename T>
        using type = traits::bitwise_negatable<T>;
    };

    struct bitwise_manipulable
    {
        template <typename T>
        using type = traits::bitwise_manipulable<T>;
    };
}

#endif /* !STRONG_TYPE_TRAITS_HPP */
