/*
** Created by doom on 26/10/18.
*/

#ifndef STRONG_TYPE_UNWRAP_HPP
#define STRONG_TYPE_UNWRAP_HPP

#include <utility>
#include <st/is_strong_type.hpp>

namespace st
{
    template <typename T>
    constexpr inline auto &&unwrap(T &&t) noexcept
    {
        if constexpr (is_strong_type_v<std::remove_cv_t<std::remove_reference_t<T>>>) {
            return std::forward<T>(t).value();
        } else {
            return std::forward<T>(t);
        }
    }
}

#endif /* !STRONG_TYPE_UNWRAP_HPP */
