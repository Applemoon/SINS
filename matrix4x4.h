#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "matrix.h"


class Matrix4x4 : public Matrix
{
public:
    Matrix4x4(double m11, double m12, double m13, double m14,
              double m21, double m22, double m23, double m24,
              double m31, double m32, double m33, double m34,
              double m41, double m42, double m43, double m44);
};

#endif // MATRIX4X4_H
