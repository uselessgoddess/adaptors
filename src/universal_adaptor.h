#ifndef UNIVERSAL_ADAPTOR
#define UNIVERSAL_ADAPTOR

#include <concepts>
#include <algorithm>

namespace adaptors
{

    template<typename Closure>
    struct universal_adaptor_closure
    {
        Closure callable;

        constexpr universal_adaptor_closure(Closure&& callable)
            : callable(callable)
        {
        }

        constexpr decltype(auto) operator()(auto&&... args) const
        {
            return callable(args...);
        };

        //template<typename... Args>
        //constexpr decltype(auto) operator()(auto&&... args) const
        //{
        //    sizeof...(Args);
        //    return callable(args...);
        //};
    };

    template<typename Closure>
    universal_adaptor_closure(Closure) -> universal_adaptor_closure<Closure>;

    template<typename Callable>
    struct universal_adaptor
    {
        Callable callable;

        constexpr universal_adaptor(Callable&& callable)
            : callable(callable)
        {
        }

        constexpr decltype(auto) operator()(auto&&... args) const
        {
            if constexpr (std::is_invocable_v<Callable, decltype(args)...>)
            {
                return callable(args...);
            }
            else
            {
                auto closure = [& /*like it*/](auto&& object) -> decltype(auto)
                {
                    return callable(object, args...);
                };

                return universal_adaptor_closure(std::move(closure));
            }
        };

        /*template<typename Args...>
        constexpr decltype(auto) operator()(auto&&... args) const
        {
            if constexpr (std::is_invocable_v<Callable, decltype(args)...>)
            {
                return callable(args...);
            }
            else
            {
                auto closure = [& *//*like it*//*](auto&& object) -> decltype(auto)
                {
                    return callable(object, args...);
                };

                return universal_adaptor_closure(std::move(closure));
            }
        };*/

    };

    template<typename Callable>
    decltype(auto) operator|(auto&& object, const universal_adaptor_closure<Callable>& adaptor)
    {
        return adaptor(object);
    }

    #define declare const static inline adaptors::universal_adaptor

    // small extensions lib
    declare as_adaptor = [](auto&& callable)
    {
        return adaptors::universal_adaptor<decltype(callable)>(callable);
    };
}

#endif //UNIVERSAL_ADAPTOR
