#include <universal_adaptor.h>
#include <iostream>
#include <sstream>

template<typename T>
concept to_string_castable = requires(T object)
{
    std::to_string(object);
};

template<typename T>
concept stringstream_castable = requires(T object, std::stringstream stream)
{
    stream << object;
};

template<typename T>
concept operator_castable = requires(T object)
{
    (std::string)object;
};

template<typename T>
concept as_stringable =
    to_string_castable<T> ||
    stringstream_castable<T> ||
    operator_castable<T>;

std::string as_string_impl(auto&& object)
{
    using Type = decltype(object);

    if constexpr (to_string_castable<Type>)
    {
        return std::to_string(object);
    }

    if constexpr (stringstream_castable<Type>)
    {
        std::stringstream stream;
        stream << object;
        return stream.str();
    }

    if constexpr (operator_castable<Type>)
    {
        return (std::string)object;
    }

    return "";
}

declare as_string = [](auto&& object) -> std::string
{
    return as_string_impl(object);
};

struct NamedStruct {};
struct UnnamedStruct {};

// impl for type
std::string as_string_impl(NamedStruct named)
{
    return "name";
}

int main()
{
    std::cout << '"' << (12 | as_string()) << '"' << std::endl;
    std::cout << '"' << (NamedStruct{} | as_string()) << '"' << std::endl;
    std::cout << '"' << (UnnamedStruct{} | as_string()) << '"' << std::endl;
}