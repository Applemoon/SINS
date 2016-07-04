#include "matrix4x4.h"


Matrix4x4::Matrix4x4(double m11, double m12, double m13, double m14,
                     double m21, double m22, double m23, double m24,
                     double m31, double m32, double m33, double m34,
                     double m41, double m42, double m43, double m44)
{
    cols = 4;
    rows = 4;
    std::vector<double> row(cols);

    row[0] = m11;
    row[1] = m12;
    row[2] = m13;
    row[3] = m14;
    matrix.push_back(row);

    row[0] = m21;
    row[1] = m22;
    row[2] = m23;
    row[3] = m24;
    matrix.push_back(row);

    row[0] = m31;
    row[1] = m32;
    row[2] = m33;
    row[3] = m34;
    matrix.push_back(row);

    row[0] = m41;
    row[1] = m42;
    row[2] = m43;
    row[3] = m44;
    matrix.push_back(row);
}
