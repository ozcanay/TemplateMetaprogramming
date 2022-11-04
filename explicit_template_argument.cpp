#include <iostream>

template<typename R, typename T, typename U>
R add(T t, U u)
{
    return t + u;
}

int main()
{
    // if we want the return to be of type "long long", we can use explicit template arguments. Note that here, the result parameter is the first argument, as it must be!
    auto res = add<long long>(1, 4);
    std::cout << res << ", type: " << typeid(res).name() << std::endl; // Type name of long long: x
}