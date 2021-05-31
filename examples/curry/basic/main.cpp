#include <universal_adaptor.h>
#include <universal_curry.h>
#include <iostream>

#include "../../help_lib.h"

rcurry rdiv = [](auto a, auto b)
{
    return a / b;
};

curry map = [](auto closure, std::ranges::range auto& range)
{
    for (auto& item : range)
    {
        item = closure(item);
    }
};

int main()
{
    auto div_2 = map(rdiv(2));

    std::array array{2, 4, 6};
    div_2(array);

    array | print();
}