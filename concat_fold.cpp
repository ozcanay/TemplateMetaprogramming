#include <iostream>
#include <string>

// return type will be auto!
template<typename... Args>
auto addToRight(Args... args)
{
    return (std::string("X") + ... + args); // enclosing parentheses is important.
};

template<typename... Args>
auto addToLeft(Args... args)
{
    return (args + ... + std::string("X"));
}

int main()
{
    std::cout << addToRight("1", "2", "3") << std::endl; // 123
    std::cout << addToLeft("1", "2", "3") << std::endl; // 1230
}