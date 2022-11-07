#include <iostream>

// https://stackoverflow.com/a/989518/4645121 -> show what was being used before enable_if.

template<typename T>
void foo(T t, std::enable_if_t<std::is_integral_v<T>>* = nullptr)
{
    std::cout << "integral type." << std::endl;
}

template<typename T>
void foo(T t, std::enable_if_t<!std::is_integral_v<T>>* = nullptr)
{
    std::cout << "NOT integral type." << std::endl;
}

struct A {};

int main()
{
    foo(1);
    foo(1.2);
    foo("qwe");
    foo(A{});
    foo('A');
}