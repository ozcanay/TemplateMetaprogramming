#include <iostream>

template<int... Args>
struct Adder;

template<int M, int... N>
struct Adder<M, N...> // do not forget angle brackets here. you are specializing!
{
    static const int value = M + Adder<N...>::value;
};

template<>
struct Adder<>
{
    static const int value = 0;
};

int main()
{
    std::cout << Adder<1, 2, 3, 4, 5>::value << std::endl;
    std::cout << Adder<>::value << std::endl;
}