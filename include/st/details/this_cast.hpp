/*
** Created by doom on 26/10/18.
*/

#ifndef STRONG_TYPE_CRTP_HELPER_HPP
#define STRONG_TYPE_CRTP_HELPER_HPP

namespace st::details
{
    template <template <typename ...> typename T>
    struct this_cast
    {
        template <typename To>
        constexpr const To *this_as() const noexcept
        {
            return static_cast<const To *>(this);
        }

        template <typename To>
        constexpr To *this_as() noexcept
        {
            return static_cast<To *>(this);
        }
    };
}

#endif /* !STRONG_TYPE_CRTP_HELPER_HPP */
