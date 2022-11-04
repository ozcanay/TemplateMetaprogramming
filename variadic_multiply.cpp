#include <iostream>

// general structure.
template<int... Args>
struct Multiply;

// core.
template<int M, int... N>
struct Multiply<M, N...>
{
    static const int value = M * Multiply<N...>::value;
};

// base case.
template<>
struct Multiply<>
{
    static const int value = 1;
};

int main()
{
    std::cout << Multiply<1, 2, 3, 4, 5>::value << std::endl;
    // std::cout << Multiply<1.1, 2.2>::value << std::endl; => does not work, g++ error message: could not convert ‘1.1000000000000001e+0’ from ‘double’ to ‘int’
}