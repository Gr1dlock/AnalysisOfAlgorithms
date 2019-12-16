#include <iostream>

#include "travellingsalesman.h"

int main()
{
    srand(time(nullptr));
    Matrix<double> matrix = { { 0, 8, 7, 1, 5, 5, 4, 9, 4, 3 },
                               { 8, 0, 8, 7, 8, 5, 9, 4, 2, 2 },
                               { 7, 8, 0, 7, 7, 4, 6, 9, 2, 9 },
                               { 1, 7, 7, 0, 2, 1, 2, 2, 10, 5 },
                               { 5, 8, 7, 2, 0, 9, 1, 8, 3, 2 },
                               { 5, 5, 4, 1, 9, 0, 9, 4, 1, 6 },
                               { 4, 9, 6, 2, 1, 9, 0, 3, 3, 1 },
                               { 9, 4, 9, 2, 8, 4, 3, 0, 6, 8 },
                               { 4, 2, 2, 10, 3, 1, 3, 6, 0, 7 },
                               { 3, 2, 9, 5, 2, 6, 1, 8, 7, 0 } };
    matrix.print();
    Route result = ant(matrix, 100, 0.5, 0.5);
    std::cout << "Ant result: " << result.length << " length" << std::endl;
    for (const auto &element: result.path)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    result = bruteForce(matrix);
    std::cout << "Brute force result: " << result.length << " length" << std::endl;
    for (const auto &element: result.path)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    return 0;
}
