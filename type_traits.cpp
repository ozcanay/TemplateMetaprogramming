#include <type_traits>
#include <concepts>

// https://stackoverflow.com/questions/62644070/differences-between-stdis-convertible-and-stdconvertible-to-in-practice
// https://en.cppreference.com/w/cpp/concepts/convertible_to

struct From;
struct To {
    explicit To(From) = delete;
};
struct From {
    operator To();
};


// std::is_convertible<From, To> (the type trait) checks is type From is implicitly convertible to type To.
// std::convertible_to<From, To> (the concept) checks that From is **both** implicitly and **explicitly** convertible to To.
static_assert(std::is_convertible_v<From, To>);
static_assert(not std::convertible_to<From, To>);

int main()
{

}