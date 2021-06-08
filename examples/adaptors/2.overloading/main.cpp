#include <universal_adaptor.h>
#include <iostream>

// easy feature 2.overloading
declare inc = [](int& object, int increment = 1) -> void
{
    object += increment;
};

// standard 2.overloading
struct rectangle
{
    float a, b;
};

rectangle& expand_impl(rectangle& self, float multiplier)
{
    self.a *= multiplier;
    self.b *= multiplier;
    return self;
};

rectangle& expand_impl(rectangle& self, float a_multiplier, float b_multiplier)
{
    self.a *= a_multiplier;
    self.b *= b_multiplier;
    return self;
};

declare expand = [](rectangle& self, auto... args) -> rectangle&
{
    return expand_impl(self, args...);
};

int main()
{
    {
        int counter = 0;

        counter | inc();
        counter | inc(1);

        counter | inc(123);

        std::cout << counter << std::endl;
    }

    {
        rectangle rectangle{ 5, 10 };

        rectangle | expand(5);
        rectangle | expand(10, 5);

        std::cout << "rectangle(" << rectangle.a << ", " << rectangle.b << ")" << std::endl;
    }
}