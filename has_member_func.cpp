// how to build this: g++ -std=c++20 has_member_func.cpp
// we specifically want to request c++20 features to be able to use concepts.

// related links:
// https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function
// https://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature?rq=1 --> THIS IS IMPORTANT. READ ALL OF THE EXAMPLES.

#include <iostream>
#include <type_traits>
#include <concepts>

// We will check for the existence of "std::string hello(int)" method. Below two are the structs defined for testing
struct WithHello {
    std::string hello(int num) const 
    {
        return "hello " + std::to_string(num);
    }
};

struct WithoutHello {
};





namespace first {
// first version.
// This should be the preferred way starting from C++20.

template<typename T>
concept has_hello_int_return_string = requires(T t) 
{
    {t.hello(0)} -> std::same_as<std::string>; // bug: this still works, if the input parameter of hello is std::string.
}; // do not forget semicolon here.



static_assert(has_hello_int_return_string<WithHello>);
static_assert(!has_hello_int_return_string<WithoutHello>);

}



namespace second {
// second version.

// need this for SFINAE to work.
template<typename T>
struct sfinae_true : std::is_same<T, std::string>{}; // note the inheritance here. instead of just inheriting from std::true_type, I will inherit from std::is_same to be able to check also the return type.

namespace detail{
    template<typename T, typename U>
    static auto test(int) -> sfinae_true<decltype(std::declval<T>().hello(std::declval<U>()))>;

    template<typename, typename U>
    static auto test(long) -> std::false_type;
}

template<typename T, typename U>
struct has_hello_int_return_string : decltype(detail::test<T, U>(0)){};

static_assert(has_hello_int_return_string<WithHello, int>());
static_assert(!has_hello_int_return_string<WithoutHello, int>());

}


// does only check the existence of the function. does not check neither the return type or the input type.
namespace third {
// third version.
// SFINAE test. we will make use of type sizes in this implementation.

// T will be the struct we are testing.
template<typename T>
class HasHello
{   
private: // below declarations do not have to be private, since the exposed variable "value" is enough.
    using one = uint8_t;
    using two = uint16_t;

    // note that we needed to use U, not T; since we cannot use T multiple times.
    template<typename U>
    static one test(decltype(&U::hello));

    template<typename U>
    static two test(...); // sink function.

public:
    static constexpr bool value = sizeof(   test<T>(0)  ) == sizeof(uint8_t); // in order to call test method here without an object, we made test method static.
};

static_assert(HasHello<WithHello>::value);
static_assert(!HasHello<WithoutHello>::value);

}


int main()
{

}