/*
** Created by doom on 26/10/18.
*/

#include <string>
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

namespace
{
    struct with_a_member :
        public st::type_base<int>,
        public st::traits::arithmetic<with_a_member>
    {
        using st::type_base<int>::type_base;

        constexpr bool is_zero() const noexcept
        {
            return value() == 0;
        }
    };
}

using name = st::type<std::string, struct name_tag>;

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
    static_assert(std::is_same_v<decltype(st::unwrap(std::declval<with_a_member &&>())), int &&>);
}

template <typename ST, typename WT>
static inline constexpr bool check_strong_type_triviality_v =
    (std::is_trivially_copy_constructible_v<ST> == std::is_trivially_copy_constructible_v<WT>) &&
    (std::is_trivially_move_constructible_v<ST> == std::is_trivially_move_constructible_v<WT>) &&
    (std::is_trivially_copy_assignable_v<ST> == std::is_trivially_copy_assignable_v<WT>) &&
    (std::is_trivially_move_constructible_v<ST> == std::is_trivially_move_constructible_v<WT>);

template <typename ST, typename WT>
static inline constexpr bool check_strong_type_noexceptness_v =
    (std::is_nothrow_copy_constructible_v<ST> == std::is_nothrow_copy_constructible_v<WT>) &&
    (std::is_nothrow_move_constructible_v<ST> == std::is_nothrow_move_constructible_v<WT>) &&
    (std::is_nothrow_copy_assignable_v<ST> == std::is_nothrow_copy_assignable_v<WT>) &&
    (std::is_nothrow_move_constructible_v<ST> == std::is_nothrow_move_constructible_v<WT>);

TEST(strong_type, triviality)
{
    static_assert(check_strong_type_triviality_v<integer, integer::value_type>);
    static_assert(check_strong_type_triviality_v<name, name::value_type>);
    static_assert(check_strong_type_triviality_v<with_a_member, int>);
}

TEST(strong_type, noexceptness)
{
    static_assert(check_strong_type_noexceptness_v<integer, integer::value_type>);
    static_assert(check_strong_type_noexceptness_v<name, name::value_type>);
    static_assert(check_strong_type_noexceptness_v<with_a_member, int>);
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

TEST(strong_type, custom_members)
{
    constexpr with_a_member wam(1);

    static_assert(wam.value() == 1);
    static_assert(!wam.is_zero());
    static_assert(with_a_member(1) > with_a_member(-1));
    static_assert((with_a_member(1) + with_a_member(2)) == with_a_member(3));
    static_assert((with_a_member(1) - with_a_member(2)) == with_a_member(-1));

    constexpr with_a_member wam2 = wam;
    static_assert(wam == wam2);
    static_assert(wam <= wam2);
    static_assert(wam >= wam2);

    with_a_member wam3(1);
    with_a_member wam4(2);
    wam4 = wam3;
    ASSERT_EQ(wam3, wam4);
    ++wam4;
    ASSERT_EQ(wam4, with_a_member(1) + wam3);
    wam4 = std::move(wam3);
    ASSERT_EQ(with_a_member(1), wam4);
}

TEST(strong_type, bitwise_manipulable)
{
    using bitwise_number = st::type<uint8_t, struct bitwise_number_tag,
        st::bitwise_manipulable, st::bitwise_orable_with<uint8_t>, st::equality_comparable>;

    static_assert((bitwise_number(1) | bitwise_number(2)) == bitwise_number(3));
    static_assert((bitwise_number(1) | 2) == bitwise_number(3));
    static_assert((bitwise_number(1) & bitwise_number(2)) == bitwise_number(0));
    static_assert(~(~bitwise_number(1)) == bitwise_number(1));
    static_assert((bitwise_number(45) ^ bitwise_number(212) ^ bitwise_number(45)) == bitwise_number(212));
}

TEST(strong_type, price_spread)
{
    using spread = st::type<
        double,
        struct spread_tag,
        st::arithmetic
    >;

    using price = st::type<
        double,
        struct price_tag,
        st::arithmetic,
        st::multiplicable_with<spread>
    >;

    constexpr price mid(120);
    constexpr spread sp(0.5);
    constexpr price pe = mid * (spread{1.0} - sp);
    static_assert(pe == price{60.0});
}
