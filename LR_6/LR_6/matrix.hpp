#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "matrix.h"

template <typename T>
Matrix<T>::Matrix()
{}

template <typename T>
Matrix<T>::Matrix(size_t size)
{
    data = std::vector<std::vector<T>> (size, std::vector<T>(size, 0));
}

template <typename T>
Matrix<T>::Matrix(size_t size, T value)
{
    data = std::vector<std::vector<T>> (size, std::vector<T>(size, value));
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &list)
{
    data = std::vector<std::vector<T>>(list.size());
    int i = 0;
    for (const auto &sublist: list)
    {
        if (list.size() != sublist.size())
        {
            throw std::length_error("Incompatible list size\n");
        }
        for (const auto &element: sublist)
        {
            data[i].push_back(element);
        }
        i++;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &other)
{
    data = other.data;
}

template <typename T>
double Matrix<T>::average() const
{
    double avg = 0.0;
    int count = 0;
    for (auto i = 0; i < size(); i++)
    {
        for (auto j = i + 1; j < size(); j++)
        {
            avg += data[i][j];
            count++;
        }
    }
    return avg / count;
}

template <typename T>
void Matrix<T>::inverse()
{
    for (auto &vec: data)
    {
        for (auto &element: vec)
        {
            element = 1.0 / element;
        }
    }
}

template<typename T>
void Matrix<T>::zero()
{
    for (auto &vec: data)
    {
        for (auto &element: vec)
        {
            element = 0;
        }
    }
}

template<typename T>
void Matrix<T>::replaceZero(const T &value)
{

    for (auto &vec: data)
    {
        for (auto &element: vec)
        {
            if (fabs(element) < EPS)
            {
                element = value;
            }
        }
    }

}

template<typename T>
void Matrix<T>::fillRandom()
{
    int element;
    for (auto i = 0; i < size(); i++)
    {
        for (auto j = i + 1; j < size(); j++)
        {
            element = MIN_DISTANCE + rand() % MAX_DISTANCE;
            data[i][j] = element;
            data[j][i] = element;
        }
    }
}

template <typename T>
template <typename U>
Matrix<T> Matrix<T>::operator * (const U &num) const
{
    Matrix<T> result(*this);
    for (auto &vec: result.data)
    {
        for (auto &element: vec)
        {
            element *= num;
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator + (const Matrix &other) const
{
    if (other.size() != size())
    {
        throw std::length_error("Incompatible matrix size\n");
    }
    Matrix<T> result(*this);
    for (size_t i = 0; i < size(); i++)
    {
        for (size_t j = 0; j < size(); j++)
        {
            result[i][j] += other[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator - (const Matrix &other) const
{
    if (other.size() != size())
    {
        throw std::length_error("Incompatible matrix size\n");
    }
    Matrix<T> result(*this);
    for (size_t i = 0; i < size(); i++)
    {
        for (size_t j = 0; j < size(); j++)
        {
            result[i][j] -= other[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> & Matrix<T>::operator = (const Matrix &other)
{
    data = other.data;
    return *this;
}

template <typename T>
template <typename U>
Matrix<T> & Matrix<T>::operator *= (const U &num)
{
    for (auto &vec: data)
    {
        for (auto &element: vec)
        {
            element *= num;
        }
    }
    return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator += (const Matrix &other)
{
    if (other.size() != size())
    {
        throw std::length_error("Incompatible matrix size\n");
    }
    for (size_t i = 0; i < size(); i++)
    {
        for (size_t j = 0; j < size(); j++)
        {
            data[i][j] += other[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator -= (const Matrix &other)
{
    if (other.size() != size())
    {
        throw std::length_error("Incompatible matrix size\n");
    }
    for (size_t i = 0; i < size(); i++)
    {
        for (size_t j = 0; j < size(); j++)
        {
            data[i][j] -= other[i][j];
        }
    }
    return *this;
}

template <typename T>
void Matrix<T>::print(void) const
{
    std::cout << "   | ";
    for (auto i = 0; i < size(); i++)
    {
        std::cout.width(2);
        std::cout << std::left << i << " ";
    }
    std::cout << std::endl;
    for (auto i = 0; i < 3 * size() + 4; i++)
        std::cout << "-";
    std::cout << std::endl;
    for (auto i = 0; i < size(); i++)
    {
        std::cout.width(3);
        std::cout << i << "| ";
        for (auto j = 0; j < size(); j++)
        {
            std::cout.width(2);
            std::cout << std::left << data[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
#endif // MATRIX_HPP
