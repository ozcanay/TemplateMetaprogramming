#include <iostream>

template<typename T, typename Pred = std::less<>> // std::less<T> can be written as std::less<>.
bool compare(T t1, T t2, Pred pred = Pred()) // = Pred() is important!
{
    return pred(t1, t2);
}

int main()
{
    std::cout << std::boolalpha;
    std::cout << compare(1, 3) << std::endl;
}