/*
** Created by doom on 26/10/18.
*/

#include <gtest/gtest.h>
#include <st/type.hpp>
#include <st/st.hpp>

using integer = st::type<
    int,
    struct integer_tag,
    st::arithmetic,
    st::addable_with<int>
>;

using acceleration = st::type<int, struct acceleration_tag>;

using speed = st::type<
    int,
    struct speed_tag,
    st::addable,
    st::subtractable,
    st::multiplicable_with<acceleration>
>;

using position = st::type<
    int,
    struct position_tag,
    st::addable_with<int>,
    st::subtractable_to<int>,
    st::orderable
>;

TEST(strong_type, is_strong_type)
{
    static_assert(!st::is_strong_type_v<int>);
    static_assert(st::is_strong_type_v<integer>);
    static_assert(st::is_strong_type_v<position>);
}

TEST(strong_type, unwrap)
{
    static_assert(std::is_same_v<decltype(st::unwrap(std::declval<const position &>())), const int &>);
    static_assert(std::is_same_v<decltype(st::unwrap(std::declval<const int &>())), const int &>);
    static_assert(std::is_same_v<decltype(st::unwrap(std::declval<position &&>())), int &&>);
    static_assert(std::is_same_v<decltype(st::unwrap(std::declval<int &&>())), int &&>);
}

TEST(strong_type, addable)
{
    static_assert((integer(1) + integer(1)).value() == integer(2).value());
    static_assert((integer(1) + 1).value() == integer(2).value());
    static_assert((position(2) + 3).value() == position(5).value());
}

TEST(strong_type, substractable)
{
    static_assert((integer(1) - integer(1)).value() == integer(0).value());
    static_assert(position(3) - position(1) == 2);
    static_assert(position(1) - position(2) == -1);
}

TEST(strong_type, multiplicable)
{
    static_assert((integer(2) * integer(4)).value() == integer(8).value());

    static_assert((speed(2) * acceleration(3)).value() == speed(6).value());
    static_assert((acceleration(3) * speed(2)).value() == speed(6).value());
}

TEST(strong_type, dividable)
{
    static_assert((integer(4) / integer(2)).value() == integer(2).value());
}

TEST(strong_type, modulable)
{
    static_assert((integer(4) % integer(2)).value() == integer(0).value());
}

TEST(strong_type, pre_incrementable)
{
    constexpr integer i = []() constexpr {
        integer ret(3);

        ++ret;
        return ret;
    }();

    static_assert(i.value() == integer(4).value());
}

TEST(strong_type, post_incrementable)
{
    constexpr integer i = []() constexpr {
        integer ret(3);

        return ret++;
    }();
    static_assert(i.value() == integer(3).value());

    constexpr integer i2 = []() constexpr {
        integer ret(3);

        ret++;
        return ret;
    }();

    static_assert(i2.value() == integer(4).value());
}

TEST(strong_type, pre_decrementable)
{
    constexpr integer i = []() constexpr {
        integer ret(4);

        --ret;
        return ret;
    }();

    static_assert(i.value() == integer(3).value());
}

TEST(strong_type, post_decrementable)
{
    constexpr integer i = []() constexpr {
        integer ret(4);

        return ret--;
    }();
    static_assert(i.value() == integer(4).value());

    constexpr integer i2 = []() constexpr {
        integer ret(4);

        ret--;
        return ret;
    }();

    static_assert(i2.value() == integer(3).value());
}

TEST(strong_type, equality_comparable)
{
    static_assert(integer(1) == integer(1));
    static_assert(integer(2) != integer(1));
}

TEST(strong_type, orderable)
{
    static_assert(integer(1) <= integer(1));
    static_assert(integer(1) >= integer(1));

    static_assert(integer(2) > integer(1));
    static_assert(integer(2) >= integer(1));
    static_assert(integer(1) < integer(2));
    static_assert(integer(1) <= integer(2));

    static_assert(position(1) < position(2));
}
