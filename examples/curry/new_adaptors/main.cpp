#include <universal_adaptor.h>
#include <universal_curry.h>
#include <iostream>
#include <ranges>

#include "../../help_lib.h"



int main()
{
    constexpr auto filter = std::views::filter | curry::as_curry();
    constexpr auto even = filter([](auto item) { return item % 2 == 0; }) | adaptors::as_adaptor();
    auto list = std::vector{1, 2, 3, 4, 5};

    for (auto item : list | even())
    {
        std::cout << item << " ";
    }
}