#include <iostream>

template<typename T>
bool isSmallerAcceptingSingleArgument(T t1, T t2)
{
    return t1 < t2;
}

// this is the most general and correct version.
template<typename T, typename U>
bool isSmaller(T t, U u)
{
    return t < u;
}

int main()
{
    std::cout << std::boolalpha;
    std::cout << isSmallerAcceptingSingleArgument(1, 5) << std::endl;
    // std::cout << isSmallerAcceptingSingleArgument(1LL, 5) << std::endl; does not compile.
    std::cout << isSmaller(1LL, 5) << std::endl;
}