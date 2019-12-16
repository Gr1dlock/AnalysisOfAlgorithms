#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <fstream>

#include "travellingsalesman.h"

struct Parameters
{
    int t;
    double alpha;
    double rho;
    double diff;
};

static std::vector<Parameters> comparison;

void writeComparison(const std::string &name)
{
    std::ofstream file;
    file.open(name, std::ios_base::app);
    if (!file)
    {
        std::cout << "Can't open file" << std::endl;
    }
    else
    {
        for (const auto &elem: comparison)
        {
            file << elem.rho << "," << elem.alpha << "," << elem.t << "," << elem.diff << '\n';
        }
        std::cout << "Comparison was written successfully" << std::endl;
        file.close();
    }
}

void sortComparison()
{
    bool flag;
    for (size_t i = 0; i < comparison.size(); i++)
    {
        flag = false;
        for (size_t j = 1; j < comparison.size() - i; j ++)
        {
            if (comparison[j].diff < comparison[j - 1].diff)
            {
                Parameters tmp = comparison[j];
                comparison[j] = comparison[j - 1];
                comparison[j - 1] = tmp;
                flag = true;
            }
        }
        if (!flag) return;
    }
}

void writeTime(const std::string &name, int &n, double &bruteTime, double &antTime)
{
    std::ofstream file;
    file.open(name, std::ios_base::app);
    if (!file)
    {
        std::cout << "Can't open file" << std::endl;
    }
    else
    {
        file << n << "," << bruteTime << "," << antTime << '\n';
        file.close();
    }
}

int main()
{
    srand(time(nullptr));
    Matrix<double> matrix = {
    { 0, 4, 8, 6, 8, 10, 9, 5, 8, 6 },
    { 4, 0, 3, 8, 7, 8, 10, 4, 9, 6 },
    { 8, 3, 0, 3, 6, 3, 6, 10, 7, 9 } ,
    { 6, 8, 3, 0, 2, 8, 5, 3, 9, 9 },
    { 8, 7, 6, 2, 0, 2, 7, 6, 6, 7 },
    { 10, 8, 3, 8, 2, 0, 6, 3, 10, 9 },
    { 9, 10, 6, 5, 7, 6, 0, 1, 7, 6 },
    { 5, 4, 10, 3, 6, 3, 1, 0, 4, 1 },
    { 8, 9, 7, 9, 6, 10, 7, 4, 0, 9 },
    { 6, 6, 9, 9, 7, 9, 6, 1, 9, 0 }};
    matrix.print();
    Route result = bruteForce(matrix);
    double diff;
    double ideal = result.length;
    for (double rho = 0; rho <= 1; rho += 0.25)
    {
        for (double alpha = 0; alpha <= 1; alpha += 0.25)
        {
            for (int t = 10; t <= 310; t += 10)
            {
                diff = 0;
                for (auto i = 0; i < 100; i++)
                {
                    result = ant(matrix, t, alpha, rho);
                    diff += result.length - ideal;
                }
                diff /= 100.0;
                comparison.push_back({t, alpha, rho, diff});
            }
        }
    }
    sortComparison();
    writeComparison("difference.txt");
    return 0;
}
