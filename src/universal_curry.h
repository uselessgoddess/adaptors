#ifndef UNIVERSAL_CURRY
#define UNIVERSAL_CURRY

#include <type_traits>
#include <algorithm>

template<typename Callable>
struct universal_curry
{
    Callable callable;

    constexpr universal_curry(Callable&& callable)
        : callable(callable)
    {
    }

    template<typename... Args>
    constexpr decltype(auto) operator()(auto&& arg) const
    {

        if constexpr (std::is_invocable_v<Callable, decltype(arg)>)
        {
            return callable(arg);
        }
        else
        {

            auto closure = [& /*like it*/](auto&&... args) -> decltype(auto)
            {
                return callable(arg, args...);
            };

            return universal_curry<decltype(closure)>(std::move(closure));
        }
    };
};

template<typename Callable>
struct universal_reverse_curry
{
    Callable callable;

    constexpr universal_reverse_curry(Callable&& callable)
        : callable(callable)
    {
    }

    template<typename... Args>
    constexpr decltype(auto) operator()(auto&& arg) const
    {

        if constexpr (std::is_invocable_v<Callable, decltype(arg)>)
        {
            return callable(arg);
        }
        else
        {

            auto closure = [& /*like it*/](auto&&... args) -> decltype(auto)
            {
                return callable(args..., arg);
            };

            return universal_curry<decltype(closure)>(std::move(closure));
        }
    };
};

#define curry constexpr inline universal_curry
#define rcurry constexpr inline universal_reverse_curry

#endif //UNIVERSAL_CURRY
