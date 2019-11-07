#include <iostream>
#include <random>
#include <chrono>
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
        double vinogradTime = 0;
        double threadedVinogradTime2 = 0;
        double threadedVinogradTime4 = 0;
        double threadedVinogradTime8 = 0;
        generateMatrix(A, i);
        generateMatrix(B, i);
        for (int j = 0; j < 10; j++)
        {
            auto time1 = std::chrono::steady_clock::now();
            vinograd(C, A, B);
            auto time2 = std::chrono::steady_clock::now();
            threadedVinograd(C, A, B, 2);
            auto time3 = std::chrono::steady_clock::now();
            threadedVinograd(C, A, B, 4);
            auto time4 = std::chrono::steady_clock::now();
            threadedVinograd(C, A, B, 8);
            auto time5 = std::chrono::steady_clock::now();
            vinogradTime += std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000.0;
            threadedVinogradTime2 += std::chrono::duration_cast<std::chrono::microseconds>(time3 - time2).count() / 1000.0;
            threadedVinogradTime4 += std::chrono::duration_cast<std::chrono::microseconds>(time4 - time3).count() / 1000.0;
            threadedVinogradTime8 += std::chrono::duration_cast<std::chrono::microseconds>(time5 - time4).count() / 1000.0;
        }
        std::cout << "Matrix size: " << i << std::endl;
        std::cout << "Vinograd time: " << vinogradTime / 10 << std::endl;
        std::cout << "2 Threaded vinograd time: " << threadedVinogradTime2 / 10 << std::endl;
        std::cout << "4 Threaded vinograd time: " << threadedVinogradTime4 / 10 << std::endl;
        std::cout << "8 Threaded vinograd time: " << threadedVinogradTime8 / 10 << std::endl;
        std::cout << std::endl;
    }
    for (int i = 101; i <= 1001; i += 100)
    {
        double vinogradTime = 0;
        double threadedVinogradTime2 = 0;
        double threadedVinogradTime4 = 0;
        double threadedVinogradTime8 = 0;
        generateMatrix(A, i);
        generateMatrix(B, i);
        for (int j = 0; j < 10; j++)
        {
            auto time1 = std::chrono::steady_clock::now();
            vinograd(C, A, B);
            auto time2 = std::chrono::steady_clock::now();
            threadedVinograd(C, A, B, 2);
            auto time3 = std::chrono::steady_clock::now();
            threadedVinograd(C, A, B, 4);
            auto time4 = std::chrono::steady_clock::now();
            threadedVinograd(C, A, B, 8);
            auto time5 = std::chrono::steady_clock::now();
            vinogradTime += std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000.0;
            threadedVinogradTime2 += std::chrono::duration_cast<std::chrono::microseconds>(time3 - time2).count() / 1000.0;
            threadedVinogradTime4 += std::chrono::duration_cast<std::chrono::microseconds>(time4 - time3).count() / 1000.0;
            threadedVinogradTime8 += std::chrono::duration_cast<std::chrono::microseconds>(time5 - time4).count() / 1000.0;
        }
        std::cout << "Matrix size: " << i << std::endl;
        std::cout << "Vinograd time: " << vinogradTime / 10 << std::endl;
        std::cout << "2 Threaded vinograd time: " << threadedVinogradTime2 / 10 << std::endl;
        std::cout << "4 Threaded vinograd time: " << threadedVinogradTime4 / 10 << std::endl;
        std::cout << "8 Threaded vinograd time: " << threadedVinogradTime8 / 10 << std::endl;
        std::cout << std::endl;
    }
    return OK;
}
