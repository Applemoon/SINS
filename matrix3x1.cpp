#include "matrix3x1.h"
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <math.h>


Matrix3x1::Matrix3x1(double m1, double m2, double m3)
{
    rows = 3;
    cols = 1;
    matrix.push_back(std::vector<double>(1, m1));
    matrix.push_back(std::vector<double>(1, m2));
    matrix.push_back(std::vector<double>(1, m3));
}


double Matrix3x1::At(int index) const
{
    return Matrix::At(index, 0);
}


void Matrix3x1::Set(int index, double value)
{
    assert(index >= 0 && index <= 2);
    matrix[index][0] = value;
}


double Matrix3x1::GetMagnitude() const
{
    return sqrt(At(0)*At(0) + At(1)*At(1) + At(2)*At(2));
}
