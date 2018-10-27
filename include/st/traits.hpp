/*
** Created by doom on 26/10/18.
*/

#ifndef STRONG_TYPE_TRAITS_HPP
#define STRONG_TYPE_TRAITS_HPP

#include <st/details/this_cast.hpp>
#include <st/unwrap.hpp>

namespace st
{
    namespace details
    {
        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct addable : details::this_cast<addable>
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
        struct subtractable : details::this_cast<subtractable>
        {
            constexpr ReturnT operator-(const OtherOperandT &other) const noexcept
            {
                return ReturnT(this_as<T>()->value() - unwrap(other));
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct multiplicable : details::this_cast<multiplicable>
        {
            constexpr ReturnT operator*(const OtherOperandT &other) const noexcept
            {
                return ReturnT(this_as<T>()->value() * unwrap(other));
            }

            template <typename _T = T, typename _Other = OtherOperandT,
                typename = std::enable_if_t<!std::is_same_v<_T, _Other>>>
            friend constexpr ReturnT operator*(const OtherOperandT &other, const T &lhs) noexcept
            {
                return ReturnT(unwrap(other) * lhs.value());
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct dividable : details::this_cast<dividable>
        {
            constexpr ReturnT operator/(const OtherOperandT &other) const noexcept
            {
                return ReturnT(this_as<T>()->value() / unwrap(other));
            }
        };

        template <typename T, typename OtherOperandT = T, typename ReturnT = T>
        struct modulable : details::this_cast<modulable>
        {
            constexpr ReturnT operator%(const OtherOperandT &other) const noexcept
            {
                return ReturnT(this_as<T>()->value() % unwrap(other));
            }
        };

        template <typename T>
        struct incrementable : details::this_cast<incrementable>
        {
            constexpr T &operator++() noexcept
            {
                ++this_as<T>()->value();
                return *this_as<T>();
            }

            constexpr const T operator++(int) noexcept
            {
                T ret(this_as<T>()->value());

                ++(this_as<T>()->value());
                return ret;
            }
        };

        template <typename T>
        struct decrementable : details::this_cast<decrementable>
        {
            constexpr T &operator--() noexcept
            {
                --this_as<T>()->value();
                return *this_as<T>();
            }

            constexpr const T operator--(int) noexcept
            {
                T ret(this_as<T>()->value());

                --(this_as<T>()->value());
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
    }

    struct addable
    {
        template <typename T>
        using type = details::addable<T>;
    };

    template <typename OtherOperandT>
    struct addable_with
    {
        template <typename T>
        using type = details::addable<T, OtherOperandT>;
    };

    struct subtractable
    {
        template <typename T>
        using type = details::subtractable<T>;
    };

    template <typename ReturnT>
    struct subtractable_to
    {
        template <typename T>
        using type = details::subtractable<T, T, ReturnT>;
    };

    struct multiplicable
    {
        template <typename T>
        using type = details::multiplicable<T>;
    };

    template <typename OtherOperandT>
    struct multiplicable_with
    {
        template <typename T>
        using type = details::multiplicable<T, OtherOperandT>;
    };

    struct dividable
    {
        template <typename T>
        using type = details::dividable<T>;
    };

    struct modulable
    {
        template <typename T>
        using type = details::modulable<T>;
    };

    struct incrementable
    {
        template <typename T>
        using type = details::incrementable<T>;
    };

    struct decrementable
    {
        template <typename T>
        using type = details::decrementable<T>;
    };

    struct equality_comparable
    {
        template <typename T>
        using type = details::equality_comparable<T>;
    };

    struct orderable
    {
        template <typename T>
        using type = details::orderable<T>;
    };

    namespace details
    {
        template <typename ...Ts>
        struct inherit : Ts ...
        {
        };
    }

    struct arithmetic
    {
        template <typename T>
        using type = details::inherit<
            typename addable::template type<T>,
            typename subtractable::template type<T>,
            typename multiplicable::template type<T>,
            typename dividable::template type<T>,
            typename modulable::template type<T>,
            typename incrementable::template type<T>,
            typename decrementable::template type<T>,
            typename equality_comparable::template type<T>,
            typename orderable::template type<T>
        >;
    };
}

#endif /* !STRONG_TYPE_TRAITS_HPP */
