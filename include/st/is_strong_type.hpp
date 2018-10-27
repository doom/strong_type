/*
** Created by doom on 26/10/18.
*/

#ifndef STRONG_TYPE_IS_STRONG_TYPE_HPP
#define STRONG_TYPE_IS_STRONG_TYPE_HPP

#include <st/type.hpp>

namespace st
{
    template <typename T>
    struct is_strong_type : std::false_type
    {
    };

    template <typename WrappedT, typename Tag, typename ...Traits>
    struct is_strong_type<type<WrappedT, Tag, Traits...>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr const bool is_strong_type_v = is_strong_type<T>::value;
}
#endif /* !STRONG_TYPE_IS_STRONG_TYPE_HPP */
