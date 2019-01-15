# strong_type
C++ implementation of strong types

## <a name="table-of-contents"></a>Table of contents

- [Table of contents](#table-of-contents)
- [What is this ?](#what-is-this)
- [A tour of the library](#library-tour)
  - [A minimal example](#minimal-example)
  - [Adding expressiveness](#adding-expressiveness)
  - [Adding strong typing](#adding-strong-typing)
  - [Customizing behavior](#customizing-behavior)
- [Examples](#examples)
  - [The easy way](#the-easy-way)
  - [The customizable way](#the-customizable-way)
- [Built-In traits](#built-ins)

## <a name="what-is-this"></a>What is this ?

This tiny library provides a way to wrap an existing type in order to give it additional meaning.
If you are already familiar with the concept of strong types, you can skip directly to the [Examples](#examples) section.

Otherwise, read along !

## <a name="library-tour"></a>A tour of the library

#### <a name="minimal-example"></a>A minimal example

Let's take a basic example: we want to represent **a distance** in our code.

The immediate idea we could have would be to use an integral type, such as `int`:

```c++
int distance_from_a_to_b = 10;
```

However, the type of the variable we work with **does not convey any information** about what its value actually represents. The only thing it tells us is how it is implemented. As a programmer reading the above code, you would need to rely on the name of the variable in order to understand the code.

#### <a name="adding-expressiveness"></a>Adding expressiveness

This can be easily fixed using a type alias:

```c++
using distance = int;
distance from_a_to_b = 10;
```

That way, our code is **more expressive**, and **easier to read** for humans.

But we still have an issue ! From the compiler's point of view, the `int` and `distance` types are identical. This can lead to error-prone constructs:

```c++
int definitely_not_a_distance = 10;
distance from_a_to_b = definitely_not_a_distance; // Ouch !
```

The code above is **not correct**, because it allows converting `definitely_not_a_distance` (which is clearly, *not a distance*) to a `distance` object implicitly.

This is the first case for which this library can help: it can "hide" the real nature of a type, in order to prevent errors and unwanted conversions.

#### <a name="adding-strong-typing"></a>Adding strong typing

In order to fully hide the implementation of a type, we use the `st::type` wrapper. It takes two (or more, but wait !) template parameters : **the type to wrap**, and **a tag** to guarantee its uniqueness.

```c++
using distance = st::type<int, struct distance_tag>;
```

*Note: the tag can be any type, as long as it is only used as tag by a single strong type*

Now, both the programmer and the compiler can distinguish a `distance` from a regular `int`.

```c++
int definitely_not_a_distance = 10;
int a_distance_value = 10;
// distance from_a_to_b = definitely_not_a_distance; // Not OK, would not compile
distance from_a_to_b = distance(a_distance); // OK
distance copy = from_a_to_b; // OK
```

As shown below, it is also possible to access the internal value of the strong type:

```c++
auto distance_value = from_a_to_b.value();
```

#### <a name="customizing-behavior"></a>Customizing behavior

Now that we created a new type that hides its underlying implementation, we also lost access to the operations supported by the underlying type.

Why is that so ? Well, in our case, the concept represented by `distance` might not support all the operations allowed by the `int` type. For example, while you can add two distances together to make a longer distance, you clearly **cannot** multiply a distance with another distance. However, you can multiply a distance with a regular number, in order to scale it.

In order to customize the behavior of our strong types, this library uses the concept of **traits**. Traits are features that can be added to a type in order to give it additional behavior. Some basic traits are provided directly by the library (see the [Built-In traits](#built-ins) section), but it is also possible to write your own.

A strong type can use traits like below:

```c++
using distance = st::type<int, struct distance_tag,
	st::addable, // distances can be added together
	st::multiplicable_with<int> // distances can be scaled by a given factor
>;
```

## <a name="examples"></a>Examples

This library provides two different ways to define strong types, each with different levels of complexity and flexibility.

#### <a name="the-easy-way" ></a>The easy way

This is the preferred way to create a basic strong type. It requires a type tag in order to guarantee the strength of the `using` alias. Custom behavior can only be added through traits. 

```c++
using integer = st::type<
    int,
    struct integer_tag,
    st::arithmetic,
    st::addable_with<int>
>;
```

#### <a name="the-customizable-way"></a>The customizable way

This way makes it easier to customize a strong type because it skips the `st::type` intermediate. Therefore, it requires creating a structure manually, which also allows defining custom member functions without having to use traits. However, traits are still available through inheritance.

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

## <a name="built-ins"></a>Built-In traits

The table below describes the built-in traits that can be applied to a given strong type `T`. Unless specified otherwise, these traits just forward the requested operation to the underlying types.

| Trait                     | Behavior                                                     |
| ------------------------- | ------------------------------------------------------------ |
| `addable`                 | Two `T` objects can be added to obtain a new `T`.            |
| `addable_with<U>`         | A `T` object can be added with a `U` object to obtain a new `T`. |
| `subtractable`            | A `T` object can be subtracted from another `T` object to obtain a new `T` |
| `subtractable_to<U>`      | A `T` object can be subtracted from another `T` object to obtain a new `U`. |
| `multiplicable`           | Two `T` objects can be multiplied to obtain a new `T`.       |
| `multiplicable_with<U>`   | A `T` object can be multiplied with a `U` object to obtain a new `T`. |
| `dividable`               | A `T` object can be divided by another `T` object to obtain a new `T`. |
| `modulable`               | A `T` object can be moduled from another `T` object to obtain a new `T`. |
| `incrementable`           | A `T` object can be pre-incremented and post-incremented.    |
| `decrementable`           | A `T` object can be pre-decremented and post-decremented.    |
| `equality_comparable`     | Two `T` objects can be compared for equality (supports `==` and `!=`). |
| `orderable`               | Two `T` objects can be ordered (supports `<`, `>`, `<=`, `>=`). |
| `arithmetic`              | Shorthand trait for `addable`, `subtractable`, `multiplicable`, `dividable`, `modulable`, `incrementable`, `decrementable`, `equality_comparable` and `orderable`. |
| `bitwise_orable`          | Two `T` objects can be bitwise `OR`-ed to obtain a new `T`.  |
| `bitwise_orable_with<U>`  | A `T` object can be bitwise `OR`-ed with a `U` object to obtain a new `T`. |
| `bitwise_andable`         | Two `T` objects can be bitwise `AND`-ed to obtain a new `T`. |
| `bitwise_andable_with<U>` | A `T` object can be bitwise `AND`-ed with a `U` object to obtain a new `T`. |
| `bitwise_xorable`         | Two `T` objects can be bitwise `XOR`-ed to obtain a new `T`. |
| `bitwise_xorable_with<U>` | A `T` object can be bitwise `XOR`-ed with a `U` object to obtain a new `T`. |
| `bitwise_negatable`       | A `T` object can be bitwise negated (`NOT`) to obtain a new `T`. |
| `bitwise_manipulable`     | Shorthand trait for `bitwise_orable`,`bitwise_orable_with`, `bitwise_andable`, `bitwise_andable_with`, `bitwise_xorable`, `bitwise_xorable_with`, `bitwise_negatable` and `bitwise_manipulable`. |
