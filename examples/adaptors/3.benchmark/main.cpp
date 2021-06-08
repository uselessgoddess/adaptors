#include <universal_adaptor.h>
#include <chrono>
#include <vector>
#include <iostream>

declare push_back = [] <typename T> (std::vector<T>& vector, const T& item)
{
    vector.push_back(item);
};

int main()
{
    {
        auto start = std::chrono::system_clock::now();
        auto vector = std::vector<int>{};

        for (int i = 0; i < 1e8; i++)
        {
            vector.push_back(i);
        }

        auto end = std::chrono::system_clock::now();
        std::cout << (end - start).count() << std::endl;

    }

    {
        auto start = std::chrono::system_clock::now();
        auto vector = std::vector<int>{};

        for (int i = 0; i < 1e8; i++)
        {
            push_back(vector, (int&&)i);
        }

        auto end = std::chrono::system_clock::now();
        std::cout << (end - start).count() << std::endl;
    }

    {
        auto start = std::chrono::system_clock::now();
        auto vector = std::vector<int>{};

        for (int i = 0; i < 1e8; i++)
        {
            push_back(i)(vector);
        }

        auto end = std::chrono::system_clock::now();
        std::cout << (end - start).count() << std::endl;
    }

    {
        auto start = std::chrono::system_clock::now();
        auto vector = std::vector<int>{};

        for (int i = 0; i < 1e8; i++)
        {
            vector | push_back(i);
        }

        auto end = std::chrono::system_clock::now();
        std::cout << (end - start).count() << std::endl;
    }
}