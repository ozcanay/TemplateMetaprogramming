// Related question: https://stackoverflow.com/questions/41301536/get-function-return-type-in-template

#include <iostream>
#include <typeinfo>
#include <type_traits>

// partial specialization for free functions.
template<typename R, typename... Args>
R extract_return_type(R(*)(Args...));

// partial specialization for member functions.
template<typename R, typename C, typename... Args>
R extract_return_type(R(C::*)(Args...));

template<typename T>
void print_name(T t)
{
    // do not forget decltype here.
    std::cout << typeid(decltype(extract_return_type(t))).name() << std::endl;
}

void func_void(){};
int func_int() {return {};}
float func_float() {return {};};
double func_double() {return {};};
struct X {
    int func_int() {return {};}
};

static_assert(std::is_same_v<decltype(extract_return_type(func_void)), void>);
static_assert(std::is_same_v<decltype(extract_return_type(func_int)), int>);
static_assert(std::is_same_v<decltype(extract_return_type(func_float)), float>);
static_assert(std::is_same_v<decltype(extract_return_type(func_double)), double>);
static_assert(std::is_same_v<decltype(extract_return_type(&X::func_int)), int>);

// second solution. Needs C++20. this is way more concise and should be the preferred way.
static_assert(std::is_same_v<std::invoke_result_t<decltype(func_void)>, void>);
static_assert(std::is_same_v<std::invoke_result_t<decltype(func_int)>, int>);
static_assert(std::is_same_v<std::invoke_result_t<decltype(func_float)>, float>);
static_assert(std::is_same_v<std::invoke_result_t<decltype(func_double)>, double>);
static_assert(std::is_same_v<std::invoke_result_t<decltype(&X::func_int), X>, int>); // this was tricky.

int main()
{
    print_name(func_void);
    print_name(func_int);
    print_name(func_float);
    print_name(func_double);
    print_name(&X::func_int);
}


