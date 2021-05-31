#ifndef HELP_LIB
#define HELP_LIB

template <std::ranges::range T>
struct const_enumerate_impl
{
    using TItem = std::ranges::range_value_t<T>;
    using TIterator = std::ranges::iterator_t<const T>;
    const T& container;

    class iterator
    {
        TIterator it;
        size_t counter = 0;

    public:
        iterator(TIterator it) :
            it(it)
        {
        }

        iterator& operator++()
        {
            ++it;
            ++counter;
            return *this;
        }

        bool operator!=(iterator other)
        {
            return it != other.it;
        }

        std::tuple<std::size_t, TItem> operator*()
        {
            return { counter, *it };
        }
    };

public:
    const_enumerate_impl(const T& t) : container(t) {}

    iterator begin()
    {
        return iterator(std::ranges::begin(container));
    }

    iterator end()
    {
        return iterator(std::ranges::end(container));
    }
};

template<typename Collection>
const_enumerate_impl(Collection) -> const_enumerate_impl<Collection>;

declare enumerate = [](std::ranges::range auto&& collection)
{
    return const_enumerate_impl(collection);
};

declare print = [](const std::ranges::range auto& collection) -> decltype(collection)
{
    std::cout << "[";
    for (auto [index, item] : collection | enumerate())
    {
        std::cout << item;
        if (index != std::ranges::size(collection) - 1)
            std::cout << ", ";
    }
    std::cout << "]";

    return collection;
};

#endif //HELP_LIB
