#ifndef MATRIX3X1_H
#define MATRIX3X1_H

#include "matrix.h"


class Matrix3x1 : public Matrix
{
public:
    Matrix3x1(double m1, double m2, double m3);

    double At(int index) const;
    void Set(int index, double value);
    double GetMagnitude() const;

    void SetX(double newX) { Set(0, newX); }
    double X() const { return At(0); }

    void SetY(double newY) { Set(1, newY); }
    double Y() const { return At(1); }

    void SetZ(double newZ) { Set(2, newZ); }
    double Z() const { return At(2); }


    void SetE(double newE) { SetX(newE); }
    double E() const { return X(); }

    void SetN(double newN) { SetY(newN); }
    double N() const { return Y(); }

    void SetUp(double newUp) { SetZ(newUp); }
    double Up() const { return Z(); }
};

#endif // MATRIX3X1_H
