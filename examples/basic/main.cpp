#include <universal_adaptor.h>
#include <iostream>

declare add = [] (int& a, int b) -> void
{
    a += b;
};

/*
    //RUST ANALOGUE

    trait AnyTraitName
    {
        fn add(&self, other: &Self) -> ();
    }

    impl AnyTraitName for i32
    {
        fn add(&self, other: &Self) -> ()
        {
            *self += *other;
        }
    }

 */

int main()
{
    int a = 1337;
    int b = 228;

    a | add(b); // a += b => 1565
    add(a, -1); // a += -1 => 1564
    add(2)(a); // a += 2 => 1566

    std::cout << a;
}