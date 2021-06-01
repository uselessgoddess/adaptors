Adaptors
====
> C++ functional library

C++ adapters is a small library that provides an interface to easily create "adapters" (extension methods)
----------



##Why adaptors?
I'm use 
[std::ranges ideology]("https://coliru.stacked-crooked.com/view?id=bef2902cc70f0044")
for create this

How to Use
----------

### Create basic adaptor

```cpp
#include <iostream> // temporary name
#include <universal_adaptor.h> // temporary name
using namespace adaptors;

struct MyStruct
{
    int value;
};

declare view =[](MyStruct& my_struct) -> void
{
    std::cout << "MyStruct: " << my_struct.value << std::endl;
};

int main()
{
    auto my_struct = MyStruct {1770113};

    my_struct | view(); // print MyStruct: 1770113
}
```

### Create template adaptor

```cpp
#include <cxxabi.h>
#include <iostream>
#include <universal_adaptor.h> // temporary name
using namespace adaptors;

declare type_id =[](auto&& self)
{
    return typeid(self);
};

declare type_name =[](auto&& self) -> std::string
{
    int status;
    std::string name = abi::__cxa_demangle(typeid(self).name(), 0, 0, &status);
    return name;
};

int main()
{
    std::cout << (type_id | type_name());
}
```

### Parody to Rust traits

#### C++

```cpp
// low-functionally parody to rust std::num
template<typename T>
concept numeric = std::integral<T> || std::floating_point<T>;

declare sign =[](numeric auto num) -> int
{
    if (num == 0)
        return 0;

    return num > 0 ? 1 : -1;
};

// usage:
12.0 | sign() // => 1
'$' | sign() // => 1
0 | sign() // => 0
-1 | sign() // => -1
```

#### Rust

```rust
trait NumSignExt
{
    fn sign(self) -> bool;
}

impl<T: std::num> NumSignExt for T
{
    fn sign(self) -> i32
    {
        if num == 0 {
            return 0;
        }

        return if num > 0 { 1 } else { -1 };
    }
}
```

### Basic overloading

```cpp
std::size_t hash_wrapper(auto&& object)
{
    return hash_impl(object);
}

declare hash = [](auto&& object) -> std::size_t
{
    return hash_wrapper(object);
};

std::size_t hash_impl(int object)
{
    return object;
}

/// for overload use overload hash_impl
```

[full example](https://github.com/uselessgoddess/adaptors/blob/main/examples/adaptors/overloading/main.cpp")

### Create universal adaptor for `push` to stl collections

```cpp
// C++ 20 like
#include
<ranges>
#include
<universal_adaptor.h> // temporary name
using namespace adaptors;

template<typename Collection>
concept push_able = requires(Collection collection, std::ranges::range_value_t<Collection> item)
{
    collection.push(item);
};

template<typename Collection>
concept push_back_able = requires(Collection collection, std::ranges::range_value_t<Collection> item)
{
    collection.push_back(item);
};

template<typename Collection>
concept universal_push_able = push_able<Collection> || push_back_able<Collection>;

declare push =[](universal_push_able auto& collection, std::ranges::range_value_t<Collection> item) -> decltype(auto); /*return ref to collection*/
{
    using Collection = decltype(collection);

    if constexpr (push_able<Collection>)
    {
        collection.push(item);
    }
    else
    {
        Collection.push_back(item);
    }
    
    return collection;
};

int main()
{
    auto vector = std::vector {1, 2, 3};
    vector | push(4) | push(5);

    // vector same as { 1, 2, 3, 4, 5 }
}
```
[full example]("https://github.com/uselessgoddess/adaptors/blob/main/examples/adaptors/traits/main.cpp")

### [more examples]("https://github.com/uselessgoddess/adaptors/blob/main/examples/adaptors/")