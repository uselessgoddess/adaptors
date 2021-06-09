#include <universal_adaptor.h>
#include <universal_curry.h>
#include <iostream>
#include <ranges>
#include <cmath>

#include "../../help_lib.h"

// FUTURE FEATURE
// curry | uncurry function

int main()
{
    static constexpr auto __lerp = std::__lerp<double>;
    static constexpr auto lerp = curry::uncurry_impl(curry::curry_impl(__lerp));

    std::cout << lerp(1)(2)(0.5) << std::endl;
    std::cout << lerp(1, 2, 0.5) << std::endl;
}
