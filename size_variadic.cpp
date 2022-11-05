#include <iostream>

// template<typename Args ...>
template<typename... Args> // this is the correct syntax.
int getSize(Args... args)
{
    // return 1 + getSize(args); -> this is what I have tried to do!
    return sizeof...(args);
}

int main()
{
    std::cout << getSize() << std::endl; // expecting 0.
    std::cout << getSize("asd") << std::endl; // expecting 1.
    std::cout << getSize(1, 2) << std::endl; // expecting 2.
    std::cout << getSize(1, "qwe", 2.3) << std::endl; // expecting 3.
}