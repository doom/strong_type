# strong_type
C++ implementation of strong types

## Example

#### The easy way
```c++
using integer = st::type<
    int,
    struct integer_tag,
    st::arithmetic,
    st::addable_with<int>
>;
```

#### The customizable way
```c++
struct int_with_a_member :
    public st::type_base<int>,
    public st::traits::arithmetic<int_with_a_member>
{
    using st::type_base<int>::type_base;

    constexpr bool is_zero() const noexcept
    {
        return value() == 0;
    }
};
```
