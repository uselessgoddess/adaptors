#include <universal_adaptor.h>
#include <iostream>
#include <concepts>
#include <functional>

// We steal the implementation
template<std::equality_comparable T>
declare equal_to = std::equal_to<T>{};

template<typename Self, bool Concept = true>
concept not_equality_comparable = (!std::equality_comparable<Self>) && Concept;

template<typename T> requires not_equality_comparable<T, std::ranges::range<T>>
struct std::equal_to<T>
{
    bool operator()(const T& self, const T& other)
    {
        return std::ranges::equal(self, other);
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << "12 == 13: " << (12 | equal_to<int>(13)) << std::endl;
    std::cout << R"("abacaba" == "abacaba": )" << (equal_to<std::string>("abacaba", "abacaba")) << std::endl;
    std::cout << "[1, 2, 3] == [1, 3, 4]: " << (equal_to<std::vector<int>>(std::vector{1, 2, 3}, std::vector{1, 3, 4})) << std::endl;
}