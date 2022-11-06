#include <iostream>

// https://stackoverflow.com/questions/20368187/when-would-i-use-stdintegral-constant-over-constexpr
// https://stackoverflow.com/questions/23976795/is-this-tag-dispatching

template<typename T>
void use_impl(const T&, std::false_type)
{
}

template<typename T>
void use_impl(const T&, std::true_type)
{
}

template<typename T>
void use(const T& v)
{
   use_impl(v, typename std::is_integral<T>::type());
}

int main()
{

}