//
// Created by Dmitriy Lugovoy on 01.11.2019.
//

#ifndef LR_4_MULTIPLICATION_H
#define LR_4_MULTIPLICATION_H

#include <vector>
#include <thread>
#include <cmath>

#define OK 0
#define ERR_EMPTY 1
#define ERR_SIZE 2

int vinograd(std::vector<std::vector<int>> &C, const std::vector<std::vector<int>> &A,
             const std::vector<std::vector<int>> &B);
int threadedVinograd(std::vector<std::vector<int>> &C, const std::vector<std::vector<int>> &A,
                     const std::vector<std::vector<int>> &B, const int &nThreads);


#endif //LR_4_MULTIPLICATION_H
