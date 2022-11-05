===

How to build:

```
g++ -std=c++20 <filename>
```

How to run:

```
./a.out
```

===

TODO:

- Explain has_member_func.cpp more.
- add zip.
- expand_all, increment all, print all parameter packs. already present in my other github repo named templates.
- to_string variadic.
- add FIBONACCI (not factorial!)
- printing type information with constexpr if
- print_variadic -> printing parameter pack.
- variable templates (NOT to be confused with variadic templates)
- add notes from you drive doc.

# 

use sizeof...(args) to find "parameter pack" size.

Fold expressions is a nice syntax to evaluate binary operators at compile-time. Fold expressions reduce parameter packs on binary operators.

# Variadic templates pattern

The usage of parameter packs obeys a typical pattern for class templates.

Perform an operation on the first element of the parameter pack and recursively invoke the operation on the remaining elements.
The recursion ends after a finite number of steps.
The boundary condition is typically a fully specialized template.

# Template Metaprogramming

Metadata and Metafunctions#
At compile-time, we speak about metadata and metafunctions instead of data and functions.

Metadata: Types and integral types that are used in metafunctions.
Metafunctions: Functions that are executed at compile-time. Class templates are used to implement metafunctions.

Return their value by ::value.
Return their type by ::type.

# std::enable_if

template< bool B, class T = void >
struct enable_if;

If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.

This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts, in particular for conditionally removing functions from the candidate set based on type traits, allowing separate function overloads or specializations based on those different type traits.

# SFINAE

"Substitution Failure Is Not An Error"


This rule applies during overload resolution of **function** templates: When substituting the explicitly specified or deduced type for the template parameter fails, the specialization is discarded from the overload set instead of causing a compile error.

This feature is used in template metaprogramming.