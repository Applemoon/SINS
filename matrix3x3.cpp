#include "matrix3x3.h"
#include <vector>


Matrix3x3::Matrix3x3(double m11, double m12, double m13,
                     double m21, double m22, double m23,
                     double m31, double m32, double m33)
{
    rows = 3;
    cols = 3;
    std::vector<double> row(cols);

    row[0] = m11;
    row[1] = m12;
    row[2] = m13;
    matrix.push_back(row);

    row[0] = m21;
    row[1] = m22;
    row[2] = m23;
    matrix.push_back(row);

    row[0] = m31;
    row[1] = m32;
    row[2] = m33;
    matrix.push_back(row);
}
