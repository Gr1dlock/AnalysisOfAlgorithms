#include <iostream>

#include <chrono>
#include "substring.h"

static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

std::string randomString(const int &length)
{
    std::string string;
    for (int i = 0; i < length; i++)
    {
        string += alphabet[rand() % 26];
    }
    return string;
}

int main()
{
    srand(time(nullptr));
    for (int i = 1000; i < 101000; i += 1000)
    {
        double time = 0;
        for (int j = 0; j < 100; j++)
        {
            std::string text = randomString(i);
            std::string substring = randomString(3);
            auto start = std::chrono::high_resolution_clock::now();
            standartSearch(text, substring);
            auto end = std::chrono::high_resolution_clock::now();
            time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
        }
        std::cout << i << " " << time / 100.0 << std::endl;
    }

    for (int i = 1000; i < 101000; i += 1000)
    {
        double time = 0;
        for (int j = 0; j < 100; j++)
        {
            std::string text = randomString(i);
            std::string substring = randomString(3);
            auto start = std::chrono::high_resolution_clock::now();
            searchKMP(text, substring);
            auto end = std::chrono::high_resolution_clock::now();
            time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
        }
        std::cout << i << " " << time / 100.0 << std::endl;
    }

    for (int i = 1000; i < 101000; i += 1000)
    {
        double time = 0;
        for (int j = 0; j < 100; j++)
        {
            std::string text = randomString(i);
            std::string substring = randomString(3);
            auto start = std::chrono::high_resolution_clock::now();
            searchBM(text, substring);
            auto end = std::chrono::high_resolution_clock::now();
            time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
        }
        std::cout << i << " " << time / 100.0 << std::endl;
    }
//    std::string text = randomString(10000);
//    std::string substring = randomString(3);
//    std::cout << standartSearch(text, substring) << " " << searchKMP(text, substring) << " " << searchBM(text, substring) << std::endl;
    return 0;
}
