#include "travellingsalesman.h"

inline double tossCoin(void)
{
    return (rand() % 100) / 100.0;
}

std::vector<int> getUnvisited(std::vector<int> &visited, const size_t &count)
{
    std::vector<int> unvisited;
    for (int i = 0; i < count; i++)
    {
        if (std::find(visited.begin(), visited.end(), i) == visited.end())
        {
            unvisited.push_back(i);
        }
    }
    return unvisited;
}

int getIndex(std::vector<int> &vec, const int& value)
{
    auto pos = std::find(vec.begin(), vec.end(), value);
    if (pos != vec.end())
    {
        return std::distance(vec.begin(), pos);
    }
    return 0;
}

Route ant(const Matrix<double> &distances, const int &tMax, const double &alpha, const double &p)
{
    const size_t nTowns = distances.size();
    // Pheromone coefficient
    const double q = distances.average() * nTowns;
    const double betta = 1 - alpha;
    // Attractions of the towns
    Matrix <double> attractions(distances);
    attractions.inverse();
    // Pheromones between towns
    Matrix<double> teta(nTowns, START_TETA);
    // Pheromone daily change
    Matrix<double> deltaTeta(nTowns);

    Route minRoute;
    minRoute.length = -1;
    std::vector<double> probabilities(nTowns, 0.0);

    for (int t = 0; t < tMax; t++)
    {
        // Day
        deltaTeta.zero();
        // Ants loop
        for (int k = 0; k < nTowns; k++)
        {
            std::vector<int> curPath = {k};
            double curLength = 0;
            int curTown = k;

            // Ants path
            std::vector<int> unvisited = getUnvisited(curPath, nTowns);
            while (curPath.size() != nTowns)
            {
                fill(probabilities.begin(), probabilities.end(), 0.0);

                // Probabilities of visiting towns
                for (const auto &town : unvisited)
                {
                    int index = getIndex(unvisited, town);
                    if (fabs(distances[curTown][town]) > EPS)
                    {
                        double sum = 0;
                        for (auto n : unvisited)
                            sum += pow(teta[curTown][n], alpha) * pow(attractions[curTown][n], betta);
                        probabilities[index] = pow(teta[curTown][town], alpha) * pow(attractions[curTown][town], betta) / sum;
                    }
                    else
                        probabilities[index] = 0;
                }

                // Choosing town
                double coin = tossCoin();
                size_t townIndex = 0;
                double curProbability = 0;
                for (size_t j = 0; j < nTowns; j++)
                {
                    curProbability += probabilities[j];
                    if (coin < curProbability)
                    {
                        townIndex = j;
                        break;
                    }
                }
                int chosenTown = unvisited[townIndex];
                curPath.push_back(chosenTown);
                curLength += distances[curTown][chosenTown];
                deltaTeta[curTown][chosenTown] += q / curLength;
                curTown = chosenTown;
                unvisited.erase(unvisited.begin() + townIndex);
            }

            // Update path
            curLength += distances[curPath[curPath.size() - 1]][curPath[0]];
            if (minRoute.length < -EPS || (curLength < minRoute.length))
            {
                minRoute.length = curLength;
                minRoute.path = curPath;
            }
        }
        // Night
        teta *= (1.0 - p);
        teta += deltaTeta;
        teta.replaceZero(MIN_TETA);
    }
    return minRoute;
}

void hamilton(const Matrix<double> &distances,Route &minRote, std::vector<int> &curPath, std::vector<bool> &visited, double &curLen)
{
    if (curPath.size() == distances.size())
    {
        double tmp = distances[curPath.back()][curPath[0]];
        if (curLen + tmp < minRote.length)
        {
            minRote.path = curPath;
            minRote.length = curLen + tmp;
        }
        return;
    }
    for (int i = 0; i < distances.size(); i++)
    {
        if (!visited[i])
        {
            double tmp = distances[curPath.back()][i];
            if (curLen + tmp > minRote.length)
                continue;
            curLen += tmp;
            curPath.push_back(i);
            visited[i] = true;
            hamilton(distances, minRote, curPath, visited, curLen);
            visited[i] = false;
            curPath.pop_back();
            curLen -= tmp;
        }
    }
}

Route bruteForce(const Matrix<double> &distances)
{
    int n = distances.size();
    std::vector<bool> visited(n, false);
    std::vector<int> curPath;
    Route minRoute;
    minRoute.length = DBL_MAX;
    double curLen = 0;
    for (int i = 0; i < n; i++)
    {
        curPath.clear();
        curPath.push_back(i);
        fill(visited.begin(), visited.end(), 0);
        visited[i] = true;
        curLen = 0;
        hamilton(distances, minRoute, curPath, visited, curLen);
    }
    return minRoute;
}
