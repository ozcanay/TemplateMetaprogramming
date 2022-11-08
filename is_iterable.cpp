#include <type_traits>
#include <vector>
#include <map>

template<typename T, typename = void>
struct is_iterable : std::false_type {};

template<typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin(), std::declval<T>().end())>> : std::true_type {};

template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

static_assert(is_iterable_v<std::vector<int>>);
static_assert(is_iterable_v<std::map<int, double>>);
static_assert(!is_iterable_v<int>);

int main()
{

}