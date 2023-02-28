// how to build this: g++ -std=c++20 has_member_func.cpp
// we specifically want to request c++20 features to be able to use concepts.

// related links:
// https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function
// https://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature?rq=1 --> THIS IS IMPORTANT. READ ALL OF THE EXAMPLES.
// https://stackoverflow.com/questions/1966362/sfinae-to-check-for-inherited-member-functions

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



// concepts. must be the default choice since C++20.

template<typename T, typename I, typename R> // T is struct, U input type, V output type.
concept ConceptHelloIntReturnsString = requires(T t)
{
    {t.hello(std::declval<I>())} -> std::same_as<R>; // this is not std::is_same. std::same_as is concept whereas std::is_same is metafunction.
    // {t.hello(U{})} -> std::same_as<V>; // U{} instead of declval also works. I will use declval to be explicit.
};

static_assert(ConceptHelloIntReturnsString<WithHello, int, std::string>);
static_assert(!ConceptHelloIntReturnsString<WithoutHello, int, std::string>);



/// expression sfinae

template<typename T, typename R>
struct sfinae_true : std::is_same<T, R>
{};

template<typename T, typename R>
static auto test(int) -> sfinae_true<decltype(std::declval<T>().hello(std::declval<int>())), R>;

template<typename T,  typename>
static auto test(long) -> std::false_type;

template<typename T, typename I, typename R>
struct ExpressionSFINAEHelloIntReturnsString : decltype(test<T, R>(std::declval<I>()))
{};

static_assert(ExpressionSFINAEHelloIntReturnsString<WithHello, int, std::string>::value); // ExpressionSFINAEHelloIntReturnsString<WithHello>() is also same. operator() is defined!
static_assert(!ExpressionSFINAEHelloIntReturnsString<WithoutHello, int, std::string>::value);



// does only check the existence of the function. does not check neither the return type or the input type.
namespace sfinae {
// third version.
// SFINAE test. we will make use of type sizes in this implementation.

// T will be the struct we are testing.
template<typename T>
class has_hello
{   
private: // below declarations do not have to be private, since the exposed variable "value" is enough.
    using one = uint8_t;
    using two = uint16_t;

    // note that we needed to use U, not T; since we cannot use T multiple times.
    template<typename U>
    static one test(decltype(&U::hello));

    template<typename U>
    static two test(...); // sink function. the lowest priority overload.

public:
    static constexpr bool value = sizeof(   test<T>(0)  ) == sizeof(uint8_t); // in order to call test method here without an object, we made test method static.
};

static_assert(has_hello<WithHello>::value);
static_assert(!has_hello<WithoutHello>::value);

}


namespace void_t {
// void_t.

template<typename, typename = void >
struct has_hello : std::false_type
{ 
};

// specialized as has_member< T , void > or discarded (sfinae)
template<typename T >
struct has_hello<T, std::void_t<decltype(&T::hello)>> : std::true_type
{ 
};

static_assert(has_hello<WithHello>::value); // Also, how can I check for input type of int. also check for return string.
static_assert(!has_hello<WithoutHello>::value);

}



namespace enable_if {
// enable_if.

template <typename T, typename = void> struct has_hello : std::false_type { };

template <typename T>
struct has_hello<T, std::enable_if_t<bool(sizeof(&T::hello))>> : std::true_type { }; // Q) why cannot I use decltype here instead of sizeof?

static_assert(has_hello<WithHello>::value);
static_assert(!has_hello<WithoutHello>::value);

}





// // I am also going to demonstrate the use of tag-dispatching before constexpr-if came along:
// namespace details {
//   template<class T>
//   bool optionalToString_helper(T obj, std::true_type /*has_to_string*/) {
//     return true;
//   }
//   template<class T>
//   bool optionalToString_helper(T obj, std::false_type /*has_to_string*/) {
//     return false;
//   }
// }
// template<class T>
// bool has_hello(T t) {
//   return details::optionalToString_helper(t, ::concepts::has_hello_int_return_string<T>);
// }

int main()
{
/*    const WithHello    with_hello;
    const WithoutHello without_hello;

    if constexpr(concepts::has_hello_int_return_string<WithHello>) {
        std::cout << "Concepts: " <<  with_hello.hello(42) << std::endl;
    } else {
        std::cout << "Concepts cannot say hi!" << std::endl;
    }

    if constexpr(expression_sfinae::has_hello_int_return_string<WithHello, int>()) {
        std::cout << "Expression SFINAE: " << with_hello.hello(42) << std::endl;
    } else {
        std::cout << "Expression SFINAE cannot say hi!" << std::endl;
    }

    if constexpr(sfinae::has_hello<WithHello>::value) {
        std::cout << "Expression SFINAE: " << with_hello.hello(42) << std::endl;
    } else {
        std::cout << "Expression SFINAE cannot say hi!" << std::endl;
    }

    if constexpr(void_t::has_hello<WithHello>::value) {
        std::cout << "void_t: " << with_hello.hello(42) << std::endl;
    } else {
        std::cout << "void_t cannot say hi!" << std::endl;
    }

    if constexpr(enable_if::has_hello<WithHello>::value) {
        std::cout << "enable_if: " << with_hello.hello(42) << std::endl;
    } else {
        std::cout << "enable_if cannot say hi!" << std::endl;
    }*/


    // I am also going to demonstrate the use of tag-dispatching:
    // if(has_hello(with_hello)) {
    //     std::cout << "tag dispatch is going to say hello: " << with_hello.hello(42) << std::endl;
    // }


}
