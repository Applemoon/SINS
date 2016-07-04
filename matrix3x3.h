#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "matrix.h"


class Matrix3x3 : public Matrix
{
public:
    Matrix3x3(double m11, double m12, double m13,
              double m21, double m22, double m23,
              double m31, double m32, double m33);
};

#endif // MATRIX3X3_H
