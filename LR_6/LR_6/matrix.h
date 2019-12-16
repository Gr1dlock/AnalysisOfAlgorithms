#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

#define MIN_DISTANCE 1
#define MAX_DISTANCE 10
#define EPS 1E-5

template <typename T>
class Matrix
{
public:
    Matrix();
    Matrix(size_t size);
    Matrix(size_t size, T value);
    Matrix(const std::initializer_list<std::initializer_list<T>> &list);
    Matrix(const Matrix<T> &other);
    inline size_t size() const { return data.size(); }
    double average() const;
    void inverse();
    void zero();
    void replaceZero(const T &value);
    void fillRandom();
    inline std::vector<T> & operator [] (size_t index) { return data[index]; }
    inline const std::vector<T> & operator [] (size_t index) const { return data[index]; }
    template <typename U>
    Matrix<T> operator * (const U &num) const;
    Matrix<T> operator + (const Matrix &other) const;
    Matrix<T> operator - (const Matrix &other) const;
    Matrix<T> & operator = (const Matrix &other);
    template <typename U>
    Matrix<T> & operator *= (const U &num);
    Matrix<T> & operator += (const Matrix &other);
    Matrix<T> & operator -= (const Matrix &other);
    void print() const;
private:
    std::vector<std::vector<T>> data;
};

#endif // MATRIX_H
