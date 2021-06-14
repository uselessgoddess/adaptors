#ifndef UNIVERSAL_ADAPTOR
#define UNIVERSAL_ADAPTOR

#include <concepts>
#include <algorithm>

namespace adaptors
{
    template<typename Closure>
    struct universal_adaptor_closure
    {
        const Closure& closure;

        constexpr universal_adaptor_closure(Closure&& closure)
            : closure(closure)
        {
        }

        template<typename Self>
        constexpr decltype(auto) operator()(Self&& self) const
        {
            return closure(std::forward<Self>(self));
        };
    };

    template<typename Closure>
    universal_adaptor_closure(Closure) -> universal_adaptor_closure<Closure>;

    template<typename Callable>
    struct universal_adaptor
    {
        Callable callable;

        constexpr universal_adaptor(Callable callable)
            : callable(callable)
        {
        }

        template<typename... Args>
        constexpr decltype(auto) operator()(Args&&... args) const
        {
            if constexpr (std::is_invocable_v<Callable, decltype(args)...>)
            {
                return callable(std::forward<Args>(args)...);
            }
            else
            {
                auto closure = [&] <typename Object> (Object&& object) -> decltype(auto)
                {
                    return callable(std::forward<Object>(object), std::forward<Args>(args)...);
                };

                return universal_adaptor_closure(std::move(closure));
            }
        };
    };

    template<typename Callable>
    constexpr decltype(auto) operator|(auto&& object, universal_adaptor_closure<Callable>&& adaptor)
    {
        return std::forward<decltype(adaptor)>(adaptor)(std::forward<decltype(object)>(object));
    }

    #define declare constexpr static inline adaptors::universal_adaptor

    // small extensions lib
    declare as_adaptor = [] <typename Callable> (Callable&& callable)
    {
        return adaptors::universal_adaptor<Callable>(callable);
    };
}

#endif //UNIVERSAL_ADAPTOR
