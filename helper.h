#ifndef HELPER_H
#define HELPER_H

#include <map>
#include "matrix3x1.h"
#include "quaternion.h"


class Helper
{
public:
    // �������� ������� ����� � �������� � ������� ������� ���������
    static double GetCurrentTime();

    // "��������������" ����������� �� �������� �������
    static double Integrate(double derivative, double timeDelta, double constant);

    // ������ ����������� �������� Ve
    static double CalcVelocityEDerivative_MPerS2(double accelerationWFE_MPerS2, double latitude_Rad,
                                                 double omegaUp_1PerS, double velocityN_MPerS,
                                                 double velocityUp_MPerS, double omegaN_1PerS);
    // ������ ����������� �������� Vn
    static double CalcVelocityNDerivative_MPerS2(double accelerationWFN_MPerS2, double latitude_Rad,
                                                 double omegaUp_1PerS, double velocityE_MPerS,
                                                 double velocityUp_MPerS, double omegaE_1PerS);

    // �������������� �����
    static double EarthEccentricity();

    // �������������� ������ ����� � ������
    static double EarthEquatorialRadius_M();

    // ������� ����� �� �������� ������
    static double EarthPhiRadius_M(double latitude_Rad);
    static double EarthLambdaRadius_M(double latitude_Rad);

    // ������� �������� �����
    static double EarthAngularSpeed_1PerS();

    // ��������� ���������� �������
    static double AccelerationOfGravity_MPerS2(double latitude_Rad, double height_M);

    // ������ ������� �������� �������� �� (����������� ������)
    static Matrix3x1 CalcAngularVelocityWF_RadPerS(double velocityN, double velocityE, double latitude_Rad, double height_M);

    // ������ �������� �������� ��
    static Matrix3x1 CalcV_MPerS(Matrix3x1 accelerationWF_MPerS2,
                                 double latitude_Rad,
                                 Matrix3x1 omega_1PerS,
                                 double timeDelta_S,
                                 Matrix3x1 velocityWF_MPerS,
                                 double gpsSpeed_MPerS,
                                 double gpsHeading_Rad,
                                 double k1,
                                 double k2,
                                 double c2,
                                 double deltaHeight_M);

    // ��������� - ������������ ��
    static Quaternion CalcUpdatingQuaternion(Matrix3x1 omega_RadPerS, double timeDelta_S);

    // ������ ����� ����������
    static Matrix3x1 CalcOrientation_Rad(Quaternion q);

    // ������� �������� � �������
    static double DegreesToRadians(double angle_Deg);
};

#endif // HELPER_H
