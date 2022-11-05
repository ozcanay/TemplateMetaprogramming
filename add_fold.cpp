#include <iostream>

template<typename... Args>
auto adder(Args... args)
{
    return (0 + ... + args); /// 0 is needed so that the template would work with no parameters, too. without 0, we would get the error: error: fold of empty expansion over operator+
}

int main()
{
    std::cout << adder(1, 2, 3, 4, 5) << std::endl;
    std::cout << adder() << std::endl;
}