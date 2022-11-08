#include <type_traits>

// we will specifically investigate if a class contains "x" member variable.

struct WithX {int x;};
struct WithoutX {};




namespace concepts {
// first version.
// This should be the preferred way starting from C++20.

template<typename T>
concept has_x = requires(T t) 
{
    t.x;
}; // do not forget semicolon here.


static_assert(has_x<WithX>);
static_assert(!has_x<WithoutX>);

}




namespace sfinae {

// no need to name the first parameter, too.
template<typename, typename = void> // since we will not use the second parameter, there is no need to write: typename = void. in fact, it is best practice not to write it, in case we use it accidentally.
struct has_x : std::false_type{};

template<typename T>
struct has_x<T, decltype((void)T::x, void())> : std::true_type{};

template <typename T>
constexpr bool has_x_v = has_x<T>::value;

static_assert(has_x_v<WithX>);
static_assert(!has_x_v<WithoutX>);

}


namespace void_t {

template<typename, typename = void>
struct has_x : std::false_type{};

// specialization
template<typename T> // note that T.x will not work! since T is a type, not an object.
struct has_x<T, std::void_t<decltype(T::x)>> : std::true_type{}; 

// Q1) why exactly do we need decltype here? -> related: https://stackoverflow.com/a/27688405/4645121

// Q2) struct has_x<T, std::void_t<typename T::x>> : std::true_type{}; why the first assert do not hold in this case?

template <typename T>
constexpr bool has_x_v = has_x<T>::value;

static_assert(has_x_v<WithX>);
static_assert(!has_x_v<WithoutX>);

}

int main()
{

}