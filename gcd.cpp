#include <iostream>

// we will demonstrate 4 versions going from the most primitive one to the most advanced one.

// First version.
// this function is too generic, it should not accept const char arrrays for example. Besides that, the function depends on only a single parameter, therefore trying to instantiate
// the template with different integer types results in an error.
template<typename T>
T gcd1(T t1, T t2)
{
    if(t2 == 0) {
        return t1;
    } else {
        return gcd1(t2, t1 % t2);
    }
}

// second version. 
// We will solve the issue of being too generic by issuing a better compiler message using static_assert. 
// The subtle difference with the first version is that we now get an exact error message and not a cryptic output of a failed template instantiation as in the first example.
template<typename T>
T gcd2(T t1, T t2)
{
    static_assert(std::is_integral<T>::value, "T should be integral type!");

    if(t2 == 0) {
        return t1;
    } else {
        return gcd2(t2, t1 % t2);
    }
}

// third version. we will now be able to provide different integer types with this version.
template<typename T1, typename T2>

// note typename and "::type" here.
typename std::common_type<T1, T2>::type gcd3(T1 t1, T2 t2) // auto return type will not work here; providing int and long long we get the error: inconsistent deduction for auto return type: ‘int’ and then ‘long long int’
{
    static_assert(std::is_integral<T1>::value, "T1 should be integral!");
    static_assert(std::is_integral<T2>::value, "T2 should be integral!");

    if(t2 == 0) {
        return t1;
    } else {
        return gcd3(t2, t1 % t2);
    }
}

template<typename T1, typename T2,
        typename std::enable_if<std::is_integral<T1>::value, bool>::type = true, // If std::enable_if returns false as first parameter, std::enable_if will have **no** member type. therefore this line would not be valid. This is not an error but a common technique in C++: SFINAE.
        typename std::enable_if<std::is_integral<T2>::value, bool>::type = true, 
        typename R = typename std::conditional<(sizeof(T1) < sizeof(T2)), T1, T2>::type // result type. std::conditional acts like **ternary operator** of compile time programming.
    >
R gcd4(T1 t1, T2 t2)
{
    // no need to static_assert thanks to std::enable_if.
    if(t2 == 0) {
        return t1;
    } else {
        return gcd3(t2, t1 % t2);
    }
}     

int main()
{
    // invoking the first version.
    std::cout << gcd1(27, 72) << std::endl;
    // std::cout << gcd1(27, 72LL) << std::endl; // ERROR: deduced conflicting types.
    // std::cout << gcd1("qwe", "asd") << std::endl; // ERROR: invalid operands of types ‘const char*’ and ‘const char*’ to binary ‘operator%’

    // invoking the second version.
    std::cout << gcd2(27, 72) << std::endl;
    // std::cout << gcd2("qwe", "asd") << std::endl; // ERROR.

    // invoking the third version.
    std::cout << gcd3(27, 72) << std::endl;
    std::cout << gcd3(27, 72LL) << std::endl;

    // invoking the fourth version
    std::cout << gcd4(27, 72) << std::endl; 
    std::cout << gcd4(27, 72LL) << std::endl; 
    // std::cout << "gcd(3.5, 4.0)= " << gcd4(3.5, 4.0) << std::endl; // ERROR: template argument deduction/substitution failed.  error: no type named ‘type’ in ‘struct std::enable_if<false, bool>’
}