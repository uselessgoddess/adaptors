#ifndef CURRY_IMPL
#define CURRY_IMPL

#include <type_traits>
#include <algorithm>

#include <universal_adaptor.h>
#include <iostream>

namespace curry
{

    template<typename Callable>
    struct curry_impl
    {
        Callable callable;

        constexpr curry_impl(Callable&& callable)
            : callable(callable)
        {
        }

        constexpr decltype(auto) operator()(auto&& arg) const
        {
            if constexpr (std::is_invocable_v<Callable, decltype(arg)>)
            {
                return callable(arg);
            }
            else
            {
                auto closure = [&](auto&& ... args) -> decltype(callable(arg, args...))
                {
                    return callable(arg, args...);
                };

                return curry_impl<decltype(closure)>(std::move(closure));
            }
        }
    };

    template<typename Callable>
    struct uncurry_impl
    {
        Callable callable;

        constexpr uncurry_impl(Callable&& callable)
            : callable(callable)
        {
        }

        constexpr decltype(auto) operator()(auto&& ... args) const
        {
            return __for_each_args(callable, args...);
        };

    private:
        static constexpr auto __for_each_args(auto&& func, auto&& arg, auto&& ... args)
        {
            if constexpr (sizeof...(args) == 0)
            {
                return func(arg);
            }
            else
            {
                return __for_each_args(func(arg), args...);
            }
        }
    };

    template<typename Callable>
    struct reverse_curry_impl
    {
        Callable callable;

        constexpr reverse_curry_impl(Callable&& callable)
            : callable(callable)
        {
        }

        constexpr decltype(auto) operator()(auto&& arg) const
        {
            if constexpr (std::is_invocable_v<Callable, decltype(arg)>)
            {
                return callable(arg);
            }
            else
            {
                auto closure = [&](auto&& ... args) -> decltype(callable(args..., arg))
                {
                    return callable(args..., arg);
                };

                return reverse_curry_impl<decltype(closure)>(std::move(closure));
            }
        }
    };

    template<typename Callable>
    struct reverse_uncurry_impl
    {
        Callable callable;

        constexpr reverse_uncurry_impl(Callable&& callable)
            : callable(callable)
        {
        }

        constexpr decltype(auto) operator()(auto&& ... args) const
        {
            return __for_each_args(callable, args...);
        };

    private:
        static constexpr auto __for_each_args(auto&& func, auto&& arg, auto&& ... args)
        {
            if constexpr (sizeof...(args) == 0)
            {
                return func(arg);
            }
            else
            {
                return __for_each_args(func(arg), args...);
            }
        }
    };

    template<typename Callable>
    curry_impl(Callable&&) -> curry_impl<Callable>;

    template<typename Callable>
    uncurry_impl(Callable&&) -> uncurry_impl<Callable>;

    template<typename Callable>
    reverse_curry_impl(Callable&&) -> reverse_curry_impl<Callable>;

    template<typename Callable>
    reverse_uncurry_impl(Callable&&) -> reverse_uncurry_impl<Callable>;


    #define currying constexpr static inline curry::curry_impl

    declare as_curry = [](auto&& callable)
    {
        return uncurry_impl(curry_impl(callable));
    };

}

#endif //CURRY_IMPL
