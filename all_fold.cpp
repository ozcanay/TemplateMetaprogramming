#include <iostream>

template<typename... Args>
bool allTrue(Args... args)
{
    return (... && args); // we did not provide a default value for the case when the parameter pack is empty. however logical AND (&&) has the default value of true.
}

int main()
{
    std::cout << std::boolalpha;
    std::cout << allTrue() << std::endl;
    std::cout << allTrue(true) << std::endl;
    std::cout << allTrue(true, true) << std::endl;
    std::cout << allTrue(true, false, true) << std::endl;
}