//
// Created by Dmitriy Lugovoy on 01.11.2019.
//

#include "multiplication.h"
#include <iostream>

int vinograd(std::vector<std::vector<int>> &C, const std::vector<std::vector<int>> &A,
        const std::vector<std::vector<int>> &B)
{
    int m = A.size();
    int n = B.size();
    if (m == 0 || n == 0)
        return ERR_EMPTY;
    if (A[0].size() != n)
        return ERR_SIZE;
    int q = B[0].size();

    std::vector<int> mulA(m,0);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n - 1; j += 2)
        {
            mulA[i] -= A[i][j] * A[i][j + 1];
        }
    }

    std::vector<int> mulB(q,0);
    for (int i = 0; i < q; i++)
    {
        for (int j = 0; j < n - 1; j += 2)
        {
            mulB[i] -= B[j][i] * B[j + 1][i];
        }
    }

    int last = n - 1;
    bool flag = n % 2 == 1;
    C = std::vector<std::vector<int>> (m, std::vector<int> (q, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            int tmp = mulA[i] + mulB[j];
            for (int k = 0; k < n - 1; k += 2)
            {
                tmp += (A[i][k] + B[k + 1][j]) * (A[i][k + 1] + B[k][j]);
            }
            if (flag)
            {
                tmp += A[i][last] * B[last][j];
            }
            C[i][j] = tmp;
        }
    }
    return OK;
}

void computeMulA(std::vector<int> &mulA, std::vector<std::vector<int>> A, int startRow, int endRow)
{
    int n = A[0].size();
    for (int i = startRow; i < endRow; i++)
    {
        for (int j = 0; j < n - 1; j += 2)
        {
            mulA[i] -= A[i][j] * A[i][j + 1];
        }
    }
}

void computeMulB(std::vector<int> &mulB, std::vector<std::vector<int>> B, int startCol, int endCol)
{
    int n = B.size();
    for (int i = startCol; i < endCol; i++)
    {
        for (int j = 0; j < n - 1; j += 2)
        {
            mulB[i] -= B[j][i] * B[j + 1][i];
        }
    }
}

void computeResult(std::vector<std::vector<int>> &C, std::vector<std::vector<int>> A,
                   std::vector<std::vector<int>> B, std::vector<int> mulA,
                   std::vector<int> mulB, int startRow, int endRow)
{
    int n = B.size();
    int q = B[0].size();
    int last = n - 1;
    bool flag = n % 2 == 1;
    for (int i = startRow; i < endRow; i++)
    {
        for (int j = 0; j < q; j++)
        {
            int tmp = mulA[i] + mulB[j];
            for (int k = 0; k < n - 1; k += 2)
            {
                tmp += (A[i][k] + B[k + 1][j]) * (A[i][k + 1] + B[k][j]);
            }
            if (flag)
            {
                tmp += A[i][last] * B[last][j];
            }
            C[i][j] = tmp;
        }
    }
}

int threadedVinograd(std::vector<std::vector<int>> &C, const std::vector<std::vector<int>> &A,
             const std::vector<std::vector<int>> &B, const int &nThreads)
{
    int m = A.size();
    int n = B.size();
    if (m == 0 || n == 0)
        return ERR_EMPTY;
    if (A[0].size() != n)
        return ERR_SIZE;
    int q = B[0].size();
    std::vector<std::thread> threads;
    std::vector<int> mulA(m,0);
    double start = 0;
    double del = m / static_cast<double>(nThreads);
    for (int i = 0; i < nThreads; i++)
    {
        threads.push_back(std::thread(computeMulA, std::ref(mulA), A, round(start),
                                      round(start + del)));
        start += del;
    }
    for (auto &thread: threads)
    {
        thread.join();
    }
    start = 0;
    del = q / static_cast<double>(nThreads);
    std::vector<int> mulB(q,0);
    for (int i = 0; i < nThreads; i++)
    {
        threads[i] = std::thread(computeMulB, std::ref(mulB), B,
                                 round(start), round(start + del));
        start += del;
    }
    for (auto &thread: threads)
    {
        thread.join();
    }

    C = std::vector<std::vector<int>> (m, std::vector<int> (q, 0));
    start = 0;
    del = m / static_cast<double>(nThreads);
    for (int i = 0; i < nThreads; i++)
    {
        threads[i] = std::thread(computeResult, std::ref(C), A, B,
                                 mulA, mulB, round(start), round(start + del));
        start += del;
    }
    for (auto &thread: threads)
    {
        thread.join();
    }
    return OK;
}
