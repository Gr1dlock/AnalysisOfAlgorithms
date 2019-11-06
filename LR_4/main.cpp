#include <iostream>
#include <random>
#include <ctime>
#include "multiplication.h"

void printMatrix(const std::vector<std::vector<int>> &matrix)
{
    for (const auto &i : matrix)
    {
        for (int j : i)
        {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
}

void generateMatrix(std::vector<std::vector<int>> &matrix, const int &size)
{
    matrix = std::vector<std::vector<int>> (size, std::vector<int>(size));
    auto randomNumberBetween = [](int low, int high)
    {
        auto randomFunc = [distribution_ = std::uniform_int_distribution<int>(low, high),
                random_engine_ = std::mt19937{ std::random_device{}() }]() mutable
        {
            return distribution_(random_engine_);
        };
        return randomFunc;
    };
    for (auto &i : matrix)
    {
        std::generate(begin(i), end(i), randomNumberBetween(1, 100));
    }
}

int main()
{
    std::vector<std::vector<int>> A;
    std::vector<std::vector<int>> B;
    std::vector<std::vector<int>> C;

    for (int i = 100; i <= 1000; i += 100)
    {
        clock_t vinogradTime = 0;
        clock_t threadedVinogradTime2 = 0;
        clock_t threadedVinogradTime4 = 0;
        generateMatrix(A, i);
        generateMatrix(B, i);
        for (int j = 0; j < 10; j++)
        {
            clock_t time1 = clock();
            vinograd(C, A, B);
            clock_t time2 = clock();
            threadedVinograd(C, A, B, 4);
            clock_t time3 = clock();
            threadedVinograd(C, A, B, 8);
            clock_t time4 = clock();
            vinogradTime += time2 - time1;
            threadedVinogradTime2 += time3 - time2;
            threadedVinogradTime4 += time4 - time3;
        }
        std::cout << "Matrix size: " << i << std::endl;
        std::cout << "Vinograd time: " << vinogradTime / 10 << std::endl;
        std::cout << "2 Threaded vinograd time: " << threadedVinogradTime2 / 10 << std::endl;
        std::cout << "4 Threaded vinograd time: " << threadedVinogradTime4 / 10 << std::endl;
        std::cout << std::endl;
    }
    return OK;
}
