#include <universal_adaptor.h>
#include <iostream>

declare ref_inc = [](int& self) -> int&
{
    self++;
    return self;
};

declare const_inc = [](int self) -> int
{
    self++;
    return self;
};

template <typename T>
declare foo = [](T) {};

int main()
{
    int ref_v = 12;
    ref_v | ref_inc() | ref_inc() | ref_inc();
    std::cout << ref_v << std::endl;

    int const_v = 12;
    std::cout << (const_v | ref_inc() | ref_inc() | ref_inc()) << std::endl;
}