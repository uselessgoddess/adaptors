#include <universal_adaptor.h>
#include <iostream>
#include <algorithm>

namespace lib
{
    namespace details
    {
        void ltrim(std::string& s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](char ch)
            {
                return !std::isspace(ch);
            }));
        }

        void rtrim(std::string& s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](char ch)
            {
                return !std::isspace(ch);
            }).base(), s.end());
        }

        void trim(std::string& s)
        {
            ltrim(s);
            rtrim(s);
        }
    }

    // Can use attribute [[maybe_unused]] that avoid compiler warnings

    inline namespace uncopy
    {
        [[maybe_unused]] declare rtrim = [](std::string& string) -> std::string&
        {
            details::rtrim(string);
            return string;
        };

        [[maybe_unused]] declare ltrim = [](std::string& string) -> std::string&
        {
            details::ltrim(string);
            return string;
        };

        [[maybe_unused]] declare trim = [](std::string& string) -> std::string&
        {
            details::trim(string);
            return string;
        };

        declare trim_single = [](std::string& string, char char_to_trim) -> std::string&
        {
            if (string.empty())
            {
                return string;
            }

            if (string.size() == 1)
            {
                if (string[0] == char_to_trim)
                {
                    string = "";
                }
            }
            else
            {
                auto left = 0;
                auto right = string.size() - 1;
                if (string[left] == char_to_trim)
                {
                    left++;
                }
                if (string[right] == char_to_trim)
                {
                    right--;
                }
                string = string.substr(left, right - left + 1);
            }

            return string;
        };

        [[maybe_unused]] declare in_brackets = [](std::string& string, std::pair<char, char> brackets = { '(', ')' }) -> std::string&
        {
            if (string.front() != brackets.first)
                string.insert(0, 1, brackets.first);

            if (string.back() != brackets.second)
                string.insert(string.size(), 1, brackets.second);
        };
    }

    namespace copy
    {
        [[maybe_unused]] declare rtrim = [](std::string string) -> std::string
        {
            uncopy::rtrim(string);
            return string;
        };

        [[maybe_unused]] declare ltrim = [](std::string string) -> std::string
        {
            uncopy::ltrim(string);
            return string;
        };

        [[maybe_unused]] declare trim = [](std::string string) -> std::string
        {
            uncopy::trim(string);
            return string;
        };

        [[maybe_unused]] declare trim_single = [](std::string string, char char_to_trim) -> std::string
        {
            uncopy::trim_single(string, char_to_trim);
            return string;
        };

        [[maybe_unused]] declare in_brackets = [](std::string string, std::pair<char, char> brackets = { '(', ')' }) -> std::string
        {
            uncopy::in_brackets(string, brackets);
            return string;
        };
    }
}

int main()
{
    {
        std::string string = " i like a code ";
        string
            | lib::ltrim()
            | lib::rtrim()
            | lib::in_brackets();

        std::cout << string << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "(" << ("   Goodbye World    " | lib::copy::ltrim()) << ")" << std::endl;
        std::cout << "(" << ("   Goodbye World    " | lib::copy::rtrim()) << ")" << std::endl;
        std::cout << "(" << ("   Goodbye World    " | lib::copy::trim()) << ")" << std::endl;
        std::cout << std::endl;
    }

    {
        std::string string = "  [_A_]  "
                             | lib::copy::trim()
                             | lib::copy::trim_single('[')
                             | lib::copy::trim_single(']')
                             | lib::copy::trim_single('_')
                             | lib::copy::in_brackets(std::pair{ '{', '}' });

        /// Pipe vs REAL PROCEDURAL SYNTAX
        /*
         std::string string = lib::copy::in_brackets(
         |  lib::copy::trim_single(
         |  |    lib::copy::trim_single(
         |  |    |    lib::copy::trim_single(
         |  |    |    |    lib::copy::trim
         |  |    |    |    ("  [_A_]  "),
         |  |    |    |--->'['),
         |  |    |------->']'),
         |  |----------->'_'),
         |------------->std::pair{'{', '}'});
         */

        std::cout << string << std::endl;
    }
}