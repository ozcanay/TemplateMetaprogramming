#include <iostream>

// https://stackoverflow.com/questions/4173254/what-is-the-curiously-recurring-template-pattern-crtp
// https://stackoverflow.com/questions/262254/crtp-to-avoid-dynamic-polymorphism

template<typename Derived>
struct Base
{
    // this is the key.
    void interface() {
        static_cast<Derived*>(this)->impl();
    }

    void impl() {
        std::cout << "Base impl()" << std::endl;
    }
};

struct Derived1 : public Base<Derived1> {
    void impl() {
        std::cout << "Derived1 impl()" << std::endl;
    }
};

struct Derived2 : public Base<Derived2> {
    void impl() {
        std::cout << "Derived2 impl()" << std::endl;
    }
};

// Especially interesting is the method "Base::impl". This method plays the role of a default implementation for the static polymorphism for the class "Derived3".
struct Derived3 : public Base<Derived3> {
};


template<typename T>
void execute(T& t)
{
    t.interface();
}

int main()
{
    // second way demos.
    Derived1 derived1;
    execute(derived1);

    Derived2 derived2;
    execute(derived2);

    Derived3 derived3;
    execute(derived3);
}