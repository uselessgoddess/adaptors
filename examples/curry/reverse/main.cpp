#include <universal_adaptor.h>
#include <universal_curry.h>
#include <iostream>
#include <ranges>

#include "../../help_lib.h"

// FUTURE FEATURE
// reverse curry and other callable object
//
// syntax
/*
    constexpr auto divides = std::divides<int>{} | curry::reverse();

    .......

    vector | std::views::transform(divides(2)); // divide elements by two
*/

int main()
{
    static constexpr auto write_two = [](auto first, auto second)
    {
        std::cout << first << " " << second << std::endl;
    };

    constexpr static auto curry_write_two = write_two | curry::as_curry();

    write_two(1, 2);
    curry_write_two(1)(2);

    constexpr static auto reverse_curry_write_two = curry::reverse_curry_impl(write_two);

    reverse_curry_write_two(1)(2);

    constexpr static auto reverse_write_two = curry::uncurry_impl(reverse_curry_write_two);

    reverse_write_two(1, 2);
}
