#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <numeric>

// a very primitive concept declaration
template <class T>
concept integral = std::is_integral_v<T>;

// a concept declaration that also specifies the return type.
template<typename T>
concept Hashable = requires(T a)
{
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

// There are 4 ways to write *Constrained* C++20 function templates:

// first
template<Hashable T>
void f1(T) {
}

// second
template<typename T> 
requires Hashable<T>
void f2(T) {
}

// third. second and third are very similar. It is just that the third version requires clause as the last part of a function declaration.
template<typename T>
void f3(T) requires Hashable<T> {
}

// fourth. I think this is the most concise way, and should be the default method to use the constrained function templates.
void f4(Hashable auto t) {
}

struct NotHashable {

};







template<typename T>
concept has_string_data_member = requires(T v) { 
    { v.name_ } -> std::convertible_to<std::string>; 
};

struct Person {
    int age_ { 0 };
    std::string name_;
};

struct Box {
    double weight_ { 0.0 };
    double volume_ { 0.0 };
};




// The above concept restricts an “interface” for basic clocks. We require that it has the three member functions, but we **don’t** specify what type do they return.
template <typename T>
concept Clock = requires(T c) { 
    c.start();  
    c.stop();
    c.getTime();
};




// std::integral and std::floating_point are concepts!
template <typename T> 
requires std::integral<T> || std::floating_point<T>
constexpr double average(const std::vector<T> &vec) {
    const double sum = std::accumulate(vec.begin(), vec.end(), 0.0);        
    return sum / vec.size();
}


int main()
{
    f1(std::string("abc")); // Compiles.
    f2(std::string("abc")); // Compiles.
    f3(std::string("abc")); // Compiles.
    f4(std::string("abc")); // Compiles.
    // f1(NotHashable{}); // Error: "NotHashable" does not satisfy "Hashable" concept.

    static_assert(has_string_data_member<Person>);
    static_assert(!has_string_data_member<Box>);
    
    std::vector ints { 1, 2, 3, 4, 5};
    std::cout << average(ints) << '\n';  

    // std::vector strings {"abc", "xyz"};
    // auto test = average(strings); // compile error: required by the constraints of ‘template<class T>  requires (integral<T>) || (floating_point<T>) constexpr double average(const std::vector<T>&)’
}