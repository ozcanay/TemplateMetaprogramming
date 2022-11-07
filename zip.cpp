/* Inputs:

Vector<1, 2, 3>
Vector<2, 3, 4>
Vector<3, 4, 5>
Output:

Vector<6, 24, 60>

*/

#include <type_traits>

// we will build up gradually.

// first, we will have to think about how to model vector. this is how we are going to represent "Vector"s as it will only contain integers.
template<int... vals>
struct Vector;

// we will implement template with specializing the primary template. So, we will first have to **declare** a primary template.
template<typename...>
struct zipTwoVectors;

// It will be assumed that we have only 2 vectors as a starting point.
template<int... Ts, int... Us>
struct zipTwoVectors<Vector<Ts...>, Vector<Us...>> {
    using type = typename zipTwoVectors<Vector<(Ts * Us)...>>::type;
};

template<typename T>
struct zipTwoVectors<T> {
    using type = T;
};




//////// a more generic solution:



template<typename...>
struct zipArbitrary;

// now, we can build on this solution to make it possible for zip to take arbitrary number of vectors.
// we will implement template with specializing the primary template. So, we will first have to **declare** a primary template.
template<int... Ts, int... Us, typename... Args>
struct zipArbitrary<Vector<Ts...>, Vector<Us...>, Args...> {
    using type = typename zipArbitrary<Vector<(Ts * Us)...>, Args...>::type;
};

template<typename T>
struct zipArbitrary<T> {
    using type = T;
};



static_assert(std::is_same<zipTwoVectors< Vector<2, 4, 6>, Vector<1, 2, 3>>::type, Vector<2, 8, 18>   >::value);
static_assert(std::is_same<zipArbitrary<Vector<2, 4, 6>, Vector<1, 2, 3>, Vector<3, 6, 9>>::type, Vector<6, 48, 162>>::value);

int main()
{

}