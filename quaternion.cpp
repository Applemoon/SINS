#include "quaternion.h"
#include <cmath>
#include "matrix4x4.h"
#include <iostream>

using namespace std;


Quaternion::Quaternion(double newW, double newX, double newY, double newZ) :
    w(newW), x(newX), y(newY), z(newZ)
{
    Normalize();
}


void Quaternion::SetElements(double newW, double newX, double newY, double newZ)
{
    w = newW;
    x = newX;
    y = newY;
    z = newZ;

    Normalize();
}


Matrix3x1 Quaternion::Transform(Matrix3x1 matrix) const
{
    Matrix3x3 quaternionMatrix = ToMatrix3x3();

    const double m1 = quaternionMatrix.At(0, 0) * matrix.At(0) +
                      quaternionMatrix.At(0, 1) * matrix.At(1) +
                      quaternionMatrix.At(0, 2) * matrix.At(2);

    const double m2 = quaternionMatrix.At(1, 0) * matrix.At(0) +
                      quaternionMatrix.At(1, 1) * matrix.At(1) +
                      quaternionMatrix.At(1, 2) * matrix.At(2);

    const double m3 = quaternionMatrix.At(2, 0) * matrix.At(0) +
                      quaternionMatrix.At(2, 1) * matrix.At(1) +
                      quaternionMatrix.At(2, 2) * matrix.At(2);

    return Matrix3x1(m1, m2, m3);
}


Quaternion Quaternion::Transform(Quaternion q) const
{
    Matrix4x4 quaternionMatrix = ToMatrix4x4();

    const double m0 = quaternionMatrix.At(0, 0) * q.GetW() +
                      quaternionMatrix.At(0, 1) * q.GetX() +
                      quaternionMatrix.At(0, 2) * q.GetY() +
                      quaternionMatrix.At(0, 3) * q.GetZ();

    const double m1 = quaternionMatrix.At(1, 0) * q.GetW() +
                      quaternionMatrix.At(1, 1) * q.GetX() +
                      quaternionMatrix.At(1, 2) * q.GetY() +
                      quaternionMatrix.At(1, 3) * q.GetZ();

    const double m2 = quaternionMatrix.At(2, 0) * q.GetW() +
                      quaternionMatrix.At(2, 1) * q.GetX() +
                      quaternionMatrix.At(2, 2) * q.GetY() +
                      quaternionMatrix.At(2, 3) * q.GetZ();

    const double m3 = quaternionMatrix.At(3, 0) * q.GetW() +
                      quaternionMatrix.At(3, 1) * q.GetX() +
                      quaternionMatrix.At(3, 2) * q.GetY() +
                      quaternionMatrix.At(3, 3) * q.GetZ();

    return Quaternion(m0, m1, m2, m3);
}


Matrix3x3 Quaternion::ToMatrix3x3() const
{
    double ww = w*w;
    double xx = x*x;
    double yy = y*y;
    double zz = z*z;

    return Matrix3x3(ww + xx - yy - zz, 2*(x*y - z*w),     2*(x*z + w*y),
                     2*(x*y + w*z),     ww - xx + yy - zz, 2*(y*z - w*x),
                     2*(x*z - w*y),     2*(y*z + w*x),     ww - xx - yy + zz);
}


void Quaternion::Print() const
{
    std::cout << "w = " << w << " x = " << x << " y = " << y << " z = " << z << std::endl;
}


void Quaternion::Normalize()
{
    const double magnitude = GetMagnitude();
    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}


Matrix4x4 Quaternion::ToMatrix4x4() const
{
    return Matrix4x4(w, -x, -y, -z,
                     x,  w,  z, -y,
                     y, -z,  w,  x,
                     z,  y, -x,  w);
}


double Quaternion::GetMagnitude() const
{
    return sqrt(w*w + x*x + y*y + z*z);
}
