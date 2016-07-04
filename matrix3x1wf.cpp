#include "matrix3x1wf.h"


Matrix3x1WF::Matrix3x1WF(Matrix3x1 newMatrix) : Matrix3x1(newMatrix)
{ }


Matrix3x1WF::Matrix3x1WF(float E, float N, float Up) : Matrix3x1(E, N, Up)
{ }


void Matrix3x1WF::SetE(float newE)
{
    Set(0, newE);
}


float Matrix3x1WF::E() const
{
    return At(0);
}


void Matrix3x1WF::SetN(float newN)
{
    Set(0, newN);
}


float Matrix3x1WF::N() const
{
    return At(1);
}


void Matrix3x1WF::SetUp(float newUp)
{
    Set(0, newUp);
}


float Matrix3x1WF::Up() const
{
    return At(2);
}
