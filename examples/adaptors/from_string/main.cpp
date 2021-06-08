#include <universal_adaptor.h>
#include <iostream>
#include <memory>

#include "../../help_lib.h"

template<typename Self>
struct from_str;

template<std::integral Self>
struct from_str<Self>
{
    Self operator()(const std::string& str) const
    {
        return static_cast<Self>(std::stoll(str));
    }
};

template<std::floating_point Self>
struct from_str<Self>
{
    Self operator()(const std::string& str) const
    {
        return static_cast<Self>(std::stold(str));
    }
};

template<typename Self>
declare parse = from_str<Self>{};

template<>
struct from_str<bool>
{
    bool operator()(const std::string& str) const
    {
        if (str == "true")
        {
            return true;
        }

        if (str == "false")
        {
            return false;
        }

        throw std::runtime_error("bool cannot parse from \"" + str + "\"");
    }
};

int main()
{
    namespace boost = std;

    std::cout << ("true" | parse<bool>()) << std::endl;
    std::cout << ("12.0" | parse<int>()) << std::endl;
    std::cout << ("12.2" | parse<int>()) << std::endl;
    std::cout << ("12.2" | parse<float>()) << std::endl;
}







