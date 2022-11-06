# How to build:


```g++ -std=c++20 <filename>```

# How to run:


```./a.out```

# TODO:

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

enable_if is a set of tools, available in the Standard Library since C++11, that **internally use SFINAE**. They allow to include or exclude overloads from possible function templates or class template specialization.

```
template< bool B, class T = void >
struct enable_if;
```

std::enable_if_t is valid and is by default void if and only if the condition inside it evaluates to true.

If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.

This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts, in particular for conditionally removing functions from the candidate set based on type traits, allowing separate function overloads or specializations based on those different type traits.

One of the primary uses of SFINAE can be found through enable_if expressions.

# void_t

Utility metafunction that maps a sequence of any types to the type void. This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts, in particular for conditionally removing functions from the candidate set based on whether an expression is valid in the **unevaluated context** (such as operand to decltype expression), allowing to exist separate function overloads or specializations, based on supported operations.

This metafunction is used in template metaprogramming to detect ill-formed types in SFINAE context. It can also be used to detect validity of an expression.

# Concepts

Concepts are a revolutionary approach for writing templates! They allow you to put constraints on template parameters that improve the readability of code, speed up compilation time, and give better error messages.

From one perspective, we can say that the requires expression takes a type and tries to instantiate the specified requirements. If it fails, then a given class doesn’t comply with this concept. **It’s like SFINAE** but in a friendly and easy-to-express syntax. Thanks to Concepts we can now easily detect a function, a member function or even a particular overload. This is much simpler that with complicated SFINAE techniques that we had before.

Thanks to the introduction of two new language keywords: requires and concept, you can specify a named requirement on a template argument. This makes code much more readable and less “hacky” (as with previous SFINAE based techniques).

# SFINAE

"Substitution Failure Is Not An Error". Very briefly: the compiler can reject code that “would not compile” for a given type.


This rule applies during overload resolution of **function** templates: When substituting the explicitly specified or deduced type for the template parameter fails, the specialization is discarded from the overload set instead of causing a compile error.

We can use SFINAE with enable_if and void_t. enable_if is old, void_t is newer; however concepts should be used to remove functions from the candidate set.

This feature is used in template metaprogramming.

Alternatives to SFINAE   
We have at least three things, from more conventional to the more modern in order:

1. tag dispatching
This is a much more readable version of selecting which version of a function is called. First, we define a core function, and then we call version A or B depending on some compile-time condition.

2. compile-time if
Since C++17 we have a new tool, build in the language, that allows you to check the condition at compile time - without the need to write complex templated code!

3. Concepts!


# CRTP

The acronym CRTP stands for the C++ idiom Curiously Recurring Template Pattern and is a technique in C++ in which a Derived class derives from a class template Base. The key is that Base has Derived as a template argument.

There are two typical use-cases for CRTP: Mixins and static polymorphism.

A nice example:

https://stackoverflow.com/a/26718782/4645121

# declval

```
template<class T>
typename std::add_rvalue_reference<T>::type declval() noexcept;
```

std::declval is a helper (added in C++11) that allows us to “pretend” that we have an object of some type (even if the default constructor is not available).
obtains a reference to its argument for use in unevaluated context.

Converts any type T to a reference type, making it possible to use member functions in decltype expressions without the need to go through constructors.

declval is commonly used in templates where acceptable template parameters ***may have no constructor in common***, but have the same member function whose return type is needed.

Note that declval can only be used in **unevaluated contexts** and is not required to be defined; it is an error to evaluate an expression that contains this function.

decltype cannot be called and thus never returns a value. The return type is T&& unless T is (possibly cv-qualified) void, in which case the return type is T.


# decltype

Inspects the declared type of an entity or the type and value category of an expression.

# consteval

# constinit

# constexpr if

The only difference is that if constexpr is evaluated at compile time, whereas if is not.

## Mixins

## Static Polymorphism

Static polymorphism is quite similar to dynamic polymorphism. But contrary to dynamic polymorphism with virtual methods, the dispatch of the method calls will take place at compile-time. ```std::enable_shared_from_this``` is a prime example.

# Tag Dispatching

Tag Dispatching enables us to choose a function based on type characteristics.

- The decision takes place at compile-time.
- Traits make the decision based on specific properties of an argument.
- The main benefit is performance.

An good example of tag dispatch would be how std::advance is typically implemented.
## Comparing SFINAE and Tag Dispatching

- Tag dispatch takes advantage of overload resolution to select the right overload.
- SFINAE disables a candidate by making it ineligible due to substitution failure.
Substitution failure is just what it says on the tin: Trying to substitute concrete arguments for the template parameters and encountering an error, which in the immediate context only rejects that candidate.

Sometimes, one or the other technique is easier to apply. And naturally they can be combined to great effect.

Complementary techniques are partial and full specialization. 

Apart from these two, if constexpr and concepts can often simplify things.


# Expression Templates

Expression templates are “structures representing a computation at compile-time, which are evaluated only as needed to produce efficient code for the entire computation.” This is called lazy evaluation.

#

std::declval gives you a "value" of whatever type you pass, without you needing to know how you can construct it. Note that this is only possible inside an unevaluated context, such as decltype, sizeof and others.

#

https://stackoverflow.com/questions/2172647/template-metaprogramming-difference-between-using-enum-hack-and-static-const

#

https://stackoverflow.com/a/262984/4645121 -> WRITE THIS TO CRTP. THE FIRST METHOD HAS TO BE WRITTEN.