#include <iostream>

template<typename... Args>
auto multiply(Args... args)
{
    return (1 * ... * args);
}

int main()
{
    std::cout << multiply(1, 2, 3, 4, 5) << std::endl;
}