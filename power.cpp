#include <iostream>

// will calculate M^N.
template<int M, int N>
struct Power
{
    static const int value = Power<M, N - 1>::value * M;
};

template<int M>
struct Power<M, 0>
{
    static const int value = 1;
};

int main()
{
    std::cout << Power<2, 10>::value << std::endl;
}