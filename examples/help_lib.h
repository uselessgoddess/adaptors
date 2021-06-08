#ifndef HELP_LIB
#define HELP_LIB

declare print = [](const std::ranges::range auto& collection) -> decltype(collection)
{
    std::cout << "[";

    for (int i = 0; auto&& item : collection)
    {
        std::cout << item;
        if (i != collection.size() - 1)
            std::cout << ", ";

        i++;
    }

    /*
        C positive style
        for (const auto& item : collection)
        {
            std::cout << item;
            if (&item != std::to_address(std::ranges::end(collection) - 1))
                std::cout << ", ";
        }
    */

    std::cout << "]";

    return collection;
};

#endif //HELP_LIB
