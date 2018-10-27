/*
** Created by doom on 09/10/18.
*/

#ifndef STRONG_TYPE_TYPE_HPP
#define STRONG_TYPE_TYPE_HPP

#include <utility>
#include <type_traits>

namespace st
{
    template <typename T, typename Tag, typename ...Traits>
    class type : public Traits::template type<type<T, Tag, Traits...>> ...
    {
    public:
        using value_type = T;
        using tag_type = Tag;

        explicit constexpr type(const T &t) : _t(t)
        {
        }

        explicit constexpr type(T &&t) noexcept(std::is_nothrow_move_constructible_v<T>) : _t(std::move(t))
        {
        }

        constexpr type(const type &) = default;

        constexpr type(type &&) noexcept(std::is_nothrow_move_constructible_v<T>) = default;

        constexpr type &operator=(const type &) = default;

        constexpr type &operator=(type &&) noexcept(std::is_nothrow_move_assignable_v<T>) = default;

        constexpr const T &value() const & noexcept
        {
            return _t;
        }

        constexpr T &value() & noexcept
        {
            return _t;
        }

        constexpr const T &&value() const && noexcept
        {
            return std::move(_t);
        }

        constexpr T &&value() && noexcept
        {
            return std::move(_t);
        }

    private:
        T _t;
    };
}

#endif /* !STRONG_TYPE_TYPE_HPP */
