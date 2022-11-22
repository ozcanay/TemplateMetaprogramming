https://github.com/necatiergin/cpp-kursu-kodlar

# How to build:


```g++ -std=c++20 <filename>```

# How to run:


```./a.out```

# Intro

Compile time programming topics, the big picture:

1. Tag dispatch
2. SFINAE
3. constexpr if (C++17)
4. concepts (C++20)

# Important Links

https://en.cppreference.com/w/cpp/meta

https://quuxplusone.github.io/blog/tags/#metaprogramming
https://stackoverflow.com/questions/69801126/doesnt-constraining-the-auto-in-c-defeat-the-purpose-of-it
https://stackoverflow.com/questions/4021981/use-static-assert-to-check-types-passed-to-macro
https://stackoverflow.com/questions/23095310/c-concepts-vs-static-assert
https://spectre-code.org/sfinae.html

```
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin(),
                                           std::declval<T>().end())>>
    : std::true_type {};
```

it is evidently possible to check the validity of more than one expressions in decltype.


https://nilsdeppe.com/posts/tmpl-part1
https://stackoverflow.com/questions/25680461/variadic-template-pack-expansion
https://stackoverflow.com/questions/4484982/how-to-convert-typename-t-to-string-in-c -> human readable types names with specializations.
https://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class
https://benjaminbrock.net/blog/detection_idiom.php
http://thbecker.net/articles/auto_and_decltype/section_01.html

### Advanced

https://oleksandrkvl.github.io/2021/04/02/cpp-20-overview.html
https://akrzemi1.wordpress.com/2020/05/07/ordering-by-constraints/


# Building Blocks

### Metafunction

Metafunctions receive **types** and/or integral values, and after performing some logics returns **types** and/or integral values. Normal functions manipulate values, **but the focus of a metafunction is types.**

https://iamsorush.com/posts/cpp-meta-function/


Inheritance is at the heart of type traits. Generally, we inherit from true_type, false_type or sometimes integral_constant. Since these structs have two template parameters, it is usually convenient to have two template parameters in the derived class to represent type and the value. More often than not, we will utilize the value field to check if a property holds or not.

```
template <typename T, typename U>
struct HasX : std::false_type { };
```

In this case, there's no surprise: HasX derives from std::false_type and hence HasX<bool, double>::value == false and HasX<bool, int>::value == false.

##### std::integral_constant

```
template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant; // using injected-class-name
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; } // since c++14
};
```

Notice that we have two distinct fields related to types: ```value_type``` and ```type```. In my experience, ```value``` is being used more to access the struct type itself.

```
typedef std::integral_constant<bool,true> std::true_type;
```

```
typedef std::integral_constant<bool,false> std::false_type;
```

```std::true_type``` and ```std::false_type``` are used to represent the values false and true as types. This is useful in type traits where you let a class template **inherit** from either ```std::false_type``` or ```std::true_type``` for different (partial) specializations, depending on some condition met by the template argument. Doing so allows one to test whether a given type satisfies the condition of the type trait and to obtain a compile time constant value indicating the result through access to the static value member which is inherited from either ```std::false_type``` or ```std::true_type``` or alternative through conversion of an instance of the type trait using the conversion operator.


# TODO:

- expand_all, increment all, print all parameter packs. already present in my other github repo named templates.
- to_string variadic.
- add FIBONACCI (not factorial!) -> necati had this.
- printing type information with constexpr if
- print_variadic -> printing parameter pack.
- variable templates (NOT to be confused with variadic templates)
- add notes from you drive doc.
- implement a same example with enable_if, tag dispatch, constexpr if and concepts. maybe printing integral and non-integral types.
- have a file that demonstrates the preferred approach for all topics. I think I need this, since there are gazillion ways to do same stuff.

# Misc

- use sizeof...(args) to find "parameter pack" size.

- Fold expressions is a nice syntax to evaluate binary operators at compile-time. Fold expressions reduce parameter packs on binary operators.

- You need a primary template **declaration**, otherwise the compiler wouldn't know what part of the function would be templated. But you do **NOT need to provide a primary definition.** It is also possible to declare template function as deleted: ```template<typename T> T add(T a, T b) = delete;``` to get compilation error on instantiation **instead of linker error.**

- use ```static_assert``` extensively in order to test your templates. It has no runtime cost at all.

- first primary template is found, then the specializations are considered!
- primary template is the fallback, default template.

- Note that decltype is not necessarily needed, as sizeof (and all unevaluated contexts) got that enhancement. It's just that decltype already delivers a type and as such is just cleaner. Here's a sizeof version of one of the overloads. The advantage of decltype over sizeof is also that a temporary is not introduced by specially crafted rules for function calls (https://stackoverflow.com/a/9154394/4645121)

- https://meetingcpp.com/mcpp/slides/2019/Modern%20Template%20Techniques.pdf


# Deduction

Deduction refers to the process of determining the type of a template parameter from a given argument. It applies to function templates, auto, and a few other cases (e.g. partial specialization).

In order for deduction to work, the template parameter type that is to be deduced has to appear in a **deducible context**.

However, there are also non-deduced contexts, where no deduction is possible. 

Related link: https://stackoverflow.com/a/25245676/4645121

# Two phase lookup

Templates are compiled (at least) twice:

1. Without Instantiation the template code itself is checked for syntax.
Eg: Any syntax errors such as ; etc.

2. At the time of instantiation(when the exact type is known), the template code is checked again to ensure all calls are valid for that particular type.
Eg: The template might, in turn, call functions which might not be present for that particular type.

Also note that lookup for non-dependent names is done in the first phase, whereas lookup for names that depend on a template parameter is done in the second phase. The significance is that if you call ```sqrt(1)```, then ```sqrt``` needs to be declared before the template is defined. But if you call ```sqrt(t)```, where t is an instance of a type that's a template parameter, then sqrt needn't be visible until the template is instantiated.

# Specialization vs Explicit Instantiation

```template <> void foo<int>(int& t);``` declares a specialization of the template, with potentially different body.

```template void foo<int>(int& t);``` causes an explicit instantiation of the template, but doesn't introduce a specialization. It just forces the instantiation of the template for a specific type.

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

enable_if is a set of tools, available in the Standard Library since C++11, that **internally use SFINAE**. They allow to **include or exclude** overloads from possible function templates or class template specialization.

```
template< bool B, class T = void >
struct enable_if;
```

std::enable_if_t is valid and is by default void if and only if the condition inside it evaluates to true.

If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.

This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts, in particular for conditionally removing functions from the candidate set based on type traits, allowing separate function overloads or specializations based on those different type traits.

One of the primary uses of SFINAE can be found through enable_if expressions.

https://stackoverflow.com/questions/14600201/why-should-i-avoid-stdenable-if-in-function-signatures
https://stackoverflow.com/questions/59473453/approaches-to-function-sfinae-in-c?noredirect=1&lq=1

# void_t

```
template< class ... > 
using void_t = void;
```

Utility metafunction that maps a sequence of any types to the type void. This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts, in particular for conditionally removing functions from the candidate set based on whether an expression is valid in the **unevaluated context** (such as operand to decltype expression), allowing to exist separate function overloads or specializations, based on supported operations. This helper type is often used for **detection pattern.** void_t is useful when used in combination with decltype and std::declval to **probe** if a type has certain members.

This metafunction is used in template metaprogramming to detect ill-formed types in SFINAE context. It can also be used to detect validity of an expression.

class = void is observed in void_t examples. -> the default argument has to be the exact same type as the one used in void_t for it to work.

# Concepts

Concepts are a constraint on types.

Concepts are a revolutionary approach for writing templates! They allow you to put constraints on template parameters that improve the readability of code, speed up compilation time, and give better error messages.

From one perspective, we can say that the requires expression takes a type and tries to instantiate the specified requirements. If it fails, then a given class doesn’t comply with this concept. **It’s like SFINAE** but in a friendly and easy-to-express syntax. Thanks to Concepts we can now easily detect a function, a member function or even a particular overload. This is much simpler that with complicated SFINAE techniques that we had before.

Thanks to the introduction of two new language keywords: requires and concept, you can specify a named requirement on a template argument. This makes code much more readable and less “hacky” (as with previous SFINAE based techniques).

https://www.stroustrup.com/good_concepts.pdf
https://iamsorush.com/posts/concepts-cpp/

```
// infamous `requires requires`. First `requires` is requires-clause,
// second one is requires-expression. Useful if you don't want to introduce new
// concept.
template<typename T>
requires requires(T a, T b) {a + b;}
auto f4(T x);
```


# SFINAE

SFINEA is a way of controlling overload resolution. SFINAE came up when we introduced std::enable_if. It helps to have different overloads for templates.

"Substitution Failure Is Not An Error". Very briefly: the compiler can reject code that “would not compile” for a given type. SFINAE relies on the compiler **not being allowed to produce an error** if an overloaded function isn’t valid. 

declval is really handy for our SFINAE constructions.

This rule applies during overload resolution of **function** templates: When substituting the explicitly specified or deduced type for the template parameter fails, the specialization is discarded (SFINAE'd out) from the overload set instead of causing a compile error.

We can use SFINAE with enable_if and void_t. enable_if is old, void_t is newer and easier to use; however concepts should be used to remove functions from the candidate set.

This feature is used in template metaprogramming.

Need for SFINAE is largely minimized with the concepts introduced to the language in C++20. Alternatives to SFINAE   
We have at least three things, from more conventional to the more modern in order:

1. tag dispatching
This is a much more readable version of selecting which version of a function is called. First, we define a core function, and then we call version A or B depending on some compile-time condition.

2. compile-time if
Since C++17 we have a new tool, build in the language, that allows you to check the condition at compile time - without the need to write complex templated code!

3. Concepts!

https://jguegant.github.io/blogs/tech/sfinae-introduction.html
https://www.sandordargo.com/blog/2021/06/02/different-ways-to-achieve-SFINAE


### Expression SFINAE

It's basically SFINAE on expressions. If the expression inside decltype isn't valid, well, kick the function from the VIP lounge of overloads. A common use of Expression SFINAE is when defining traits, like a trait to check if a class sports a certain member function:

# CRTP

The acronym CRTP stands for the C++ idiom Curiously Recurring Template Pattern and is a technique in C++ in which a Derived class derives from a class template Base. The key is that Base has Derived as a template argument.

There are two typical use-cases for CRTP: Mixins and static polymorphism.

A nice example:

https://stackoverflow.com/a/26718782/4645121

### Mixins

### Static Polymorphism

Static polymorphism is quite similar to dynamic polymorphism. But contrary to dynamic polymorphism with virtual methods, the dispatch of the method calls will take place at compile-time. ```std::enable_shared_from_this``` is a prime example.

# declval

```
template<class T>
typename std::add_rvalue_reference<T>::type declval() noexcept;
```

std::declval<A>() serves us well here by obviating the need for there to be any public constructor of T, or for us to know about it.

std::declval is a helper (added in C++11) that allows us to “pretend” that we have an object of some type (even if the default constructor is not available).
obtains a reference to its argument for use in unevaluated context.

Converts any type T to a reference type, making it possible to use member functions in decltype expressions without the need to go through constructors.

declval is commonly used in templates where acceptable template parameters **may have no constructor in common**, but have the same member function whose return type is needed.

Note that declval can only be used in **unevaluated contexts** and is not required to be defined; it is an error to evaluate an expression that contains this function.

decltype cannot be called and thus never returns a value. The return type is T&& unless T is (possibly cv-qualified) void, in which case the return type is T.

In my experience delcval is used commonly with references. A related question:

https://stackoverflow.com/questions/67307362/using-declval-with-a-reference-type

# decltype

Inspects the declared type of an entity or the type and value category of an expression. You will encounter ```decltype``` with expression SFINAE, tag dispatch etc. It is also common to encounter expressions that accomodate comma operator in ```decltype```. The last expression inside the decltype will dictate the type: ```decltype(serialize_imp(os, obj, 0), void())```.

# constexpr

constexpr functions might be evaluated at compile-time, if the input is known at compile-time. Otherwise, it is executed at run-time.

https://www.codingame.com/playgrounds/2205/7-features-of-c17-that-will-simplify-your-code/constexpr-if

# consteval

The consteval specifier declares a function or function template to be an immediate function, that is, every potentially evaluated call (i.e. call out of an unevaluated context) to the function must (directly or indirectly) produce a compile time constant expression. (**History lesson: It used to be spelled constexpr! in a previous revision of the paper.**) 

### consteval vs constexpr
In contrast, constexpr functions may be evaluated at compile time or run time, and need not produce a constant in all cases. consteval function is a one which is "required" to execute only at compile time.

Same as constexpr, a consteval specifier implies inline.

**At most one** of the constexpr, consteval, and constinit specifiers is allowed to appear within the same sequence of declaration specifiers.

# decay

I encounter this a lot in templated code snippets.

# constinit

constinit is invented to prevent static order initialization fiasco:

Initializing a variable with static storage duration might result in two outcomes:

1. The variable is initialized at compile-time (constant-initialization);
2. The variable is initialized the first time control passes through its declaration.

Case (2) is problematic because it can lead to the static initialization order fiasco, which is a source of dangerous bugs related to global objects.

The constinit keyword can only be applied on variables with static storage duration. If the decorated variable is not initialized at compile-time, the program is ill-formed (i.e. does not compile).

Using constinit ensures that the variable is initialized at compile-time, and that the static initialization order fiasco cannot take place.

It does **NOT** make the variable immutable. So, it does not imply const. It also does not imply constexpr. However, constexpr **does** imply constinit.


# constexpr if

The only difference is that if constexpr is evaluated at compile time, whereas if is not. if constexpr does not have to be a valid code block **inside the templated function**, if the invalid code block is not to be compiled.

# Tag Dispatching

This relies on the compiler **picking a function** from the overload set based on argument deduction. What we call "tag" is just basically an empty struct. 

An example: https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Tag_Dispatching

- The decision takes place at compile-time.
- Traits make the decision based on specific properties of an argument.
- The main benefit is performance.

An good example of tag dispatch would be how std::advance is typically implemented.

### Tag dispatching vs enum

https://stackoverflow.com/questions/47200005/what-is-the-differences-between-tag-and-enum-dispatch-in-c

If you used enum, we had to determine at runtime.

### Tag dispatching vs SFINAE vs constexpr-if

- Tag dispatch takes advantage of **overload resolution** to select the right overload. (overload resolution should be the first thing to come to your mind when tag dispatch is mentioned.)
- SFINAE disables a candidate by making it ineligible due to substitution failure.
Substitution failure is just what it says on the tin: Trying to substitute concrete arguments for the template parameters and encountering an error, which in the immediate context only rejects that candidate.

SFINAE is primarily a technique for removing overloads from candidate sets, and tag dispatching is a technique for selecting between two (or more) **overloads**. There is some overlap in functionality, but they are not equivalent.

Sometimes, one or the other technique is easier to apply. And naturally they can be combined to great effect. Tag dispatching **does not manipulate the overload set**, but helps you select exactly the function you want by providing the proper arguments through a compile-time expression (e.g. in a type trait). In my experience, this is much easier to debug and get right. If you are an aspiring library writer of sophisticated type traits, you might need enable_if somehow, but for most regular use of compile-time conditions it's not recommended.

Tag dispatch usually is faster than SFINAE because it is just overload resolution under the hood. Tag dispatch finishes as soon as a viable overload is found.

Complementary techniques are partial and full specialization. 

Apart from these two, if constexpr and concepts can often simplify things.

https://stackoverflow.com/questions/6972368/stdenable-if-to-conditionally-compile-a-member-function

https://stackoverflow.com/questions/20368187/when-would-i-use-stdintegral-constant-over-constexpr


# Expression Templates

Expression templates are “structures representing a computation at compile-time, which are evaluated only as needed to produce efficient code for the entire computation.” This is called lazy evaluation.

# std::conditional



#

std::declval gives you a "value" of whatever type you pass, without you needing to know how you can construct it. Note that this is only possible inside an unevaluated context, such as decltype, sizeof and others.

#

https://stackoverflow.com/questions/2172647/template-metaprogramming-difference-between-using-enum-hack-and-static-const

#

https://stackoverflow.com/a/262984/4645121 -> WRITE THIS TO CRTP. THE FIRST METHOD HAS TO BE WRITTEN.

# Advanced Questions

https://stackoverflow.com/questions/43470741/how-does-eric-nieblers-implementation-of-stdis-function-work

# Examples

http://www.gotw.ca/gotw/071.htm



