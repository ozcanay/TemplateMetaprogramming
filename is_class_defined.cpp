#include <type_traits>

// interesting question: https://stackoverflow.com/questions/10711952/how-to-detect-existence-of-a-class-using-sfinae?noredirect=1&lq=1


// If T is defined, it must have a destructor, and only one destructor. And that destructor is likelier to be public than any other possible member of T. 
// In that light, the simplest and strongest play we can make is to craft an SFINAE probe for the existence of T::~T.

template< typename T>
struct has_destructor
{   
    /* Has destructor :) */
    template <typename A> 
    static std::true_type test(decltype(std::declval<A>().~A()) *) {
        return std::true_type();
    }

    /* Has no destructor :( */
    template<typename A>
    static std::false_type test(...) {
        return std::false_type(); 
    }

    /* This will be either `std::true_type` or `std::false_type` */
    typedef decltype(test<T>(0)) type;

    static const bool value = type::value; /* Which is it? */
};


int main()
{

}