#include <universal_adaptor.h>
#include <iostream>
#include <random>
#include <ranges>

#include "../../help_lib.h"

declare is_power_of = [](std::integral auto self, std::integral auto power)
{
    /* other checks .... */

    if (power == 2)
    {
        return (self & (self - 1)) == 0;
    }

    while (self % power == 0)
    {
        self /= power;
    }

    return self == 1;
};

template<typename Self>
concept sizeable = requires(Self& self) { std::ranges::size(self); };

declare is_logarithmic = [](const sizeable auto& self) -> bool
{
    return std::ranges::size(self) | is_power_of(2);
};

int main()
{
    auto list = {1, 2, 3, 4};
    std::cout << (list | is_logarithmic()) << std::endl;

    int array[] {1, 2, 3, 4};
    std::cout << (array | is_logarithmic()) << std::endl;

    std::vector vector {1, 2, 3, 4};
    std::cout << (vector | is_logarithmic()) << std::endl;

    std::string string {"hello world!!!!!"};
    std::cout << (string | is_logarithmic()) << std::endl;
}
