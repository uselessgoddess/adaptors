#include <universal_adaptor.h>
#include <iostream>

#include "../help_lib.h"

// analogue rust traits

// WARNING: C++20 code
/* Small tips:
 *
 * std::ranges::range is concept which checks if the type supports foreach
 * all stl collection is std::ranges::range
 *
 * std::ranges::range_value_t<RANGE> return item type from RANGE
 * (RANGE is std::ranges::range)
 *
 *
 *
 * */

template<typename Collection>
concept __pushable = requires(Collection collection, std::ranges::range_value_t<Collection> item)
{
    requires std::ranges::range<Collection>; // collection is assumed to support foreach
    collection.push(item);
};

template<typename Collection>
concept __push_backable = requires(Collection collection, std::ranges::range_value_t<Collection> item)
{
    requires std::ranges::range<Collection>; // collection is assumed to support foreach
    collection.push_back(item);
};


declare push = [](auto& collection, auto item) -> decltype(collection)
requires
(__pushable<decltype(collection)> ||
 __push_backable<decltype(collection)>)
&&
std::same_as<std::ranges::range_value_t<decltype(collection)>, decltype(item)>
/*
 * We have Collection<ItemType>
 * requires ItemType == decltype(item)
 * */
{
    constexpr bool is_pushable = __pushable<decltype(collection)>;
    constexpr bool is_push_backable = __push_backable<decltype(collection)>;

    if constexpr (is_pushable)
    {
        collection.push(item);
        return collection;
    }

    if constexpr (is_push_backable)
    {
        collection.push_back(item);
        return collection;
    }

    static_assert(is_pushable || is_push_backable, "UNREAL");
};

// concept is a trait analogue
template<typename Collection>
concept pushable = requires(Collection collection, std::ranges::range_value_t<Collection> item)
{
    collection | push(item);
    /* same as:
     * push(collection, item);
     * push(item)(collection);
     * */
};

// use trait
declare push_default = [] <pushable Collection, typename Item = std::ranges::range_value_t<Collection>>
    (Collection& collection) -> decltype(collection)
requires std::default_initializable<Item> // if Item type might default initialize
{
    return collection | push(Item{});
};


int main()
{
    std::vector<int> vector{1, 1, 7};

    vector | push_default();
    vector | push(1);
    vector | push(3);

    vector | print();
}