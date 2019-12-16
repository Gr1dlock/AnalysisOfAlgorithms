#ifndef TRAVELLINGSALESMAN_H
#define TRAVELLINGSALESMAN_H

#include <cmath>
#include <cfloat>
#include "matrix.hpp"

#define START_TETA 10
#define MIN_TETA 5

struct Route
{
    std::vector<int> path;
    double length;
};

Route ant(const Matrix<double> &distances, const int &tMax, const double &alpha, const double &p);
Route bruteForce(const Matrix<double> &distances);

#endif // TRAVELLINGSALESMAN_H
