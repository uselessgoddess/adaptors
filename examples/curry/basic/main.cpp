#include <universal_adaptor.h>
#include <universal_curry.h>
#include <iostream>

#include "../../help_lib.h"

// make acurry function from adaptor
auto rdiv = [](auto a, auto b)
{
    return b / a;
} | curry::as_curry();

// classic style curry declaration
currying map = [](auto closure, std::ranges::range auto& range)
{
    for (auto& item : range)
    {
        item = closure(item);
    }
};

int main()
{
    auto div_2 = map(rdiv(2)) | adaptors::as_adaptor();

    std::array array{2, 4, 6};

    array | div_2();
    array | print();
}