#include <iostream>

// https://stackoverflow.com/questions/27375089/what-is-the-easiest-way-to-print-a-variadic-parameter-pack-using-stdostream -> accepted answer is WAY MORE complicated.

template<typename T, typename... Args>
void print(const T& t, const Args&... args)
{
    if constexpr (sizeof...(args) == 0) {
        // here parameter pack is drained and we have one last remaning item that has been just unpacked from the parameter pack and we have to print it, too.
        std::cout << t << std::endl;
    } else {
        std::cout << t << ' ';
        print(args...);
    }
}

int main()
{
    print(1, "aydin", 1.3, "qwe", 5);
}