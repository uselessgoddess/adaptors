#ifndef HELP_LIB
#define HELP_LIB

declare print = [](const std::ranges::range auto& collection) -> decltype(collection)
{
    std::cout << "[";

    for (const auto& item : collection)
    {
        std::cout << item;
        if (&item != &*(std::ranges::end(collection) - 1))
            std::cout << ", ";
    }
    std::cout << "]";

    return collection;
};

#endif //HELP_LIB
