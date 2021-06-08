#include <universal_adaptor.h>
#include <iostream>
// UNWRAP FLUENTS

enum DStyle
{
    _d_,
    d_,
    _d,
    d,
};

template <std::ranges::range Range>
struct print_wrapper
{
private:
    std::pair<char, char> _brackets = { '[', ']'};
    std::size_t _collum_frequency = 0;
    DStyle _delimiter_style = DStyle::d_;
    char _delimiter = ',';


public:
    const Range& range;
    constexpr print_wrapper(const Range& range) : range(range) {}

    void delimiter(char value)
    {
        _delimiter = value;
    }

    void delimiter_style(DStyle value)
    {
        _delimiter_style = value;
    }

    void collum_frequency(std::size_t value)
    {
        _collum_frequency = value;
    }

    void brackets(char first)
    {
        _brackets = {first, first};
    }

    void brackets(char first, char second)
    {
        _brackets = {first, second};
    }

    void brackets(std::pair<char, char> value)
    {
        _brackets = value;
    }

    void print() const
    {
        std::cout << _brackets.first;

        for (int i = 0; auto&& item : range)
        {
            i++;

            std::cout << item;
            if (i != std::ranges::size(range))
            {
                switch (_delimiter_style)
                {
                    case _d_:
                        std::cout << " " << _delimiter << " ";
                        break;
                    case d_:
                        std::cout << _delimiter << " ";
                        break;
                    case _d:
                        std::cout << " " << _delimiter;
                        break;
                    case d:
                        std::cout << _delimiter;
                        break;
                }

                if (_collum_frequency != 0 && i % _collum_frequency == 0)
                    std::cout << std::endl;
            }
        }

        std::cout << _brackets.second;
    }
};

#define method_to_adaptor(method_name) \
declare method_name = [] <typename Range> (print_wrapper<Range> wrapper, const auto&... args) \
{ \
    wrapper.method_name(args...); \
    return wrapper; \
};

method_to_adaptor(brackets)
method_to_adaptor(collum_frequency)
method_to_adaptor(delimiter)
method_to_adaptor(delimiter_style)

declare print = [] <std::ranges::range Range> (Range& collection)
{
    return print_wrapper<Range>(collection);
};

declare unwrap = [] <typename Range> (const print_wrapper<Range>& wrapper)
{
    wrapper.print();
};

int main()
{
    auto vector = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector
        | print()
            | collum_frequency(3)
            | brackets('|')
            | delimiter_style(DStyle::_d)
            | delimiter('^')
        | unwrap();
}