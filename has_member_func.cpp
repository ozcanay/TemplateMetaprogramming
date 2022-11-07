// how to build this: g++ -std=c++20 has_member_func.cpp
// we specifically want to request c++20 features to be able to use concepts.

// related links:
// https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function
// https://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature?rq=1 --> THIS IS IMPORTANT. READ ALL OF THE EXAMPLES.

#include <iostream>

// first version.
// This should be the preferred way starting from C++20.
template<class T>
std::string optionalToString(T* obj)
{
    constexpr bool has_toString = requires(const T& t) {
        t.toString();
    };

    if constexpr (has_toString) {
        std::cout << "object T has the method toString. calling it..." << std::endl;
        return obj->toString();
    } else {
        return "object T does not have the method toString.";
    }
}

struct ClassWithToString {
public:
    std::string toString() const
    {
        std::cout << "toString called. const version." << std::endl;
        return {};
    }

    std::string toString()
    {
        std::cout << "toString called." << std::endl;
        return {};
    }
};

struct ClassWithoutToString {
};




// second version.
#include <type_traits>
template<class>
struct sfinae_true : std::true_type{};

namespace detail{
    template<class T, class A0>
    static auto test_stream(int) -> sfinae_true<decltype(std::declval<T>().stream(std::declval<A0>()))>;

    template<class, class A0>
    static auto test_stream(long) -> std::false_type;
}

template<class T, class Arg>
struct has_stream : decltype(detail::test_stream<T, Arg>(0)){};




// third version.
// SFINAE test. we will make use of type sizes in this implementation.
template <typename T>
class has_helloworld
{
    using one = uint8_t; // size 1 byte.
    using two = uint16_t; // size 2 bytes.

    template<typename U> // cannot use T here.
    static one test(decltype(&U::helloworld));

    template<typename U>  // cannot use T here.
    static two test(...); // fallback method. the most generic one.   
public:
    // enum { value = sizeof(test<T>(0)) == sizeof(uint8_t) };
    static const int value = sizeof(test<T>(0)) == sizeof(uint8_t); // this looks more modern and explicit.
};

int main()
{
    // invoking the first method.
    ClassWithToString with_to_string;
    ClassWithoutToString without_to_string;

    std::cout << optionalToString(&with_to_string) << std::endl;
    std::cout << optionalToString(&without_to_string) << std::endl;



    // invoking the second method.
    struct X{ void stream(int){} };
    struct Y{};

    static_assert(has_stream<X, int>() == true, "fail X");
    static_assert(has_stream<Y, int>() == false, "fail Y");


    // invoking the third version.
    struct Hello
    {
        int helloworld() { return 0; }
    };
    struct Generic {};   

    std::cout << "has_helloworld<Hello>: " << has_helloworld<Hello>::value << std::endl;
    std::cout << "has_helloworld<Generic>: " << has_helloworld<Generic>::value << std::endl;
}