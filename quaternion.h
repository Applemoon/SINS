#ifndef QUATERNION_H
#define QUATERNION_H

#include "matrix3x3.h"
#include "matrix3x1.h"
#include "matrix4x4.h"

using std::vector;


class Quaternion
{
public:
    Quaternion(double newW, double newX, double newY, double newZ);
    void SetElements(double newW, double newX, double newY, double newZ); // ������ �������� �����������
    Matrix3x1 Transform(Matrix3x1 matrix) const; // ����������������� �������
    Quaternion Transform(Quaternion q) const; // ����������������� �����������
    Matrix3x3 ToMatrix3x3() const; // �������������� � ������� 3�3
    void Print() const;

    // �������� �������� �����������
    double GetW() const { return w; }
    double GetX() const { return x; }
    double GetY() const { return y; }
    double GetZ() const { return z; }

private:
    double w;
    double x;
    double y;
    double z;

    void Normalize(); // ������������ �����������
    Matrix4x4 ToMatrix4x4() const; // �������������� � ������� 4�4
    double GetMagnitude() const;
};

#endif // QUATERNION_H
