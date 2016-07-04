#include "helper.h"
#include <math.h>
#include "time.h"

#define PI 3.14159265


double Helper::GetCurrentTime()
{
    return (double)clock() / CLOCKS_PER_SEC;
}


double Helper::Integrate(double derivative, double timeDelta, double constant)
{
    return constant + derivative * timeDelta;
}


double Helper::CalcVelocityEDerivative_MPerS2(double accelerationWFE_MPerS2, double latitude_Rad,
                                              double omegaUp_1PerS, double velocityN_MPerS,
                                              double velocityUp_MPerS, double omegaN_1PerS)
{
    return accelerationWFE_MPerS2 +
            (EarthAngularSpeed_1PerS() * sin(latitude_Rad) + omegaUp_1PerS) * velocityN_MPerS -
            (EarthAngularSpeed_1PerS() * cos(latitude_Rad) + omegaN_1PerS) * velocityUp_MPerS;
}


double Helper::CalcVelocityNDerivative_MPerS2(double accelerationWFN_MPerS2, double latitude_Rad,
                                              double omegaUp_1PerS, double velocityE_MPerS,
                                              double velocityUp_MPerS, double omegaE_1PerS)
{
    return accelerationWFN_MPerS2 -
            (EarthAngularSpeed_1PerS() * sin(latitude_Rad) + omegaUp_1PerS) * velocityE_MPerS +
            velocityUp_MPerS * omegaE_1PerS;
}


double Helper::EarthEccentricity()
{
    return 0.00335281066474748071984552861852; // WGS84
}


double Helper::EarthEquatorialRadius_M()
{
    return 6378137.0; // WGS84
}


double Helper::EarthPhiRadius_M(double latitude_Rad)
{
    const double e = EarthEccentricity();
    return (EarthEquatorialRadius_M() * (1.0 - e * e)) / pow(1.0 - pow(e * sin(latitude_Rad), 2), 1.5);
}


double Helper::EarthLambdaRadius_M(double latitude_Rad)
{
    return EarthEquatorialRadius_M() / sqrt(1.0 - pow(EarthEccentricity() * sin(latitude_Rad), 2));
}


double Helper::EarthAngularSpeed_1PerS()
{
    return 0.000072921158553;
}


double Helper::AccelerationOfGravity_MPerS2(double latitude_Rad, double height)
{
    const double sinLatitude = sin(latitude_Rad);
    const double sin2Latitude = sin(2 * latitude_Rad);
    return 9.780327 * (1 + 0.0053024 * sinLatitude * sinLatitude - 0.0000058 * sin2Latitude * sin2Latitude) -
            0.000003086 * height;
}


Matrix3x1 Helper::CalcAngularVelocityWF_RadPerS(double velocityN, double velocityE, double latitude_Rad, double height_M)
{
    const double omegaE_RadPerS = -velocityN / (EarthPhiRadius_M(latitude_Rad) + height_M);
    const double omegaN_RadPerS = velocityE / (EarthLambdaRadius_M(latitude_Rad) + height_M) +
            EarthAngularSpeed_1PerS() * cos(latitude_Rad);
    const double omegaUp_RadPerS = velocityE * tan(latitude_Rad) /
            (EarthLambdaRadius_M(latitude_Rad) + height_M) + EarthAngularSpeed_1PerS() * sin(latitude_Rad);

    return Matrix3x1(omegaE_RadPerS, omegaN_RadPerS, omegaUp_RadPerS);
}


Matrix3x1 Helper::CalcV_MPerS(Matrix3x1 accelerationWF_MPerS2, double latitude_Rad,
                              Matrix3x1 omega_1PerS, double timeDelta_S, Matrix3x1 prevVelocityWF_MPerS,
                              double gpsSpeed_MPerS, double gpsHeading_Rad, double k1, double k2,
                              double c2, double deltaHeight_M)
{
    // восточная составляющая
    const double deltaVelocityWFE_MPerS = prevVelocityWF_MPerS.E() - (gpsSpeed_MPerS * sin(gpsHeading_Rad));
    const double vEDerivative_MPerS2 = CalcVelocityEDerivative_MPerS2(accelerationWF_MPerS2.E(),
                                                                      latitude_Rad,
                                                                      omega_1PerS.Up(),
                                                                      prevVelocityWF_MPerS.N(),
                                                                      prevVelocityWF_MPerS.Up(),
                                                                      omega_1PerS.N())
            - k2 * deltaVelocityWFE_MPerS;
    const double velocityE_MPerS = Integrate(vEDerivative_MPerS2,  timeDelta_S, prevVelocityWF_MPerS.E());

    // северная составляющая
    const double deltaVelocityWFN_MPerS = prevVelocityWF_MPerS.N() - (gpsSpeed_MPerS * cos(gpsHeading_Rad));
    const double velocityNDerivative_MPerS2 = CalcVelocityNDerivative_MPerS2(accelerationWF_MPerS2.N(),
                                                                             latitude_Rad,
                                                                             omega_1PerS.Up(),
                                                                             prevVelocityWF_MPerS.E(),
                                                                             prevVelocityWF_MPerS.Up(),
                                                                             omega_1PerS.E())
            - k1 * deltaVelocityWFN_MPerS;
    const double velocityN_MPerS = Integrate(velocityNDerivative_MPerS2, timeDelta_S, prevVelocityWF_MPerS.N());

    // вертикальная составляющая
    const double velosityUpDerivative_MPerS2 = accelerationWF_MPerS2.Z() - c2 * deltaHeight_M;
    const double velocityUp_MPerS = Integrate(velosityUpDerivative_MPerS2, timeDelta_S, prevVelocityWF_MPerS.Up());


    return Matrix3x1(velocityE_MPerS, velocityN_MPerS, velocityUp_MPerS);
}


Quaternion Helper::CalcUpdatingQuaternion(Matrix3x1 omega_RadPerS, double timeDelta_S)
{
    const double sinMultiplier = sin(omega_RadPerS.GetMagnitude() * timeDelta_S / 2.0) /
            omega_RadPerS.GetMagnitude();

    const double m0 = cos(omega_RadPerS.GetMagnitude() * timeDelta_S / 2.0);
    const double m1 = omega_RadPerS.X() * sinMultiplier;
    const double m2 = omega_RadPerS.Y() * sinMultiplier;
    const double m3 = omega_RadPerS.Z() * sinMultiplier;

    return Quaternion(m0, m1, m2, m3);
}


Matrix3x1 Helper::CalcOrientation_Rad(Quaternion q)
{
    const double qx2 = q.GetX() * q.GetX();
    const double qw2 = q.GetW() * q.GetW();

    const double pitch_Rad = asin(2 * (q.GetX() * q.GetY() + q.GetW() * q.GetZ()));
    const double roll_Rad = atan((q.GetW() * q.GetX() - q.GetY() * q.GetZ()) / (qw2 + qx2 - 0.5));
    const double heading_Rad = atan((q.GetW() * q.GetY() - q.GetX() * q.GetZ()) / (qw2 + qx2 - 0.5));

    return Matrix3x1(pitch_Rad, roll_Rad, heading_Rad);
}


double Helper::DegreesToRadians(double angle_Deg)
{
    return angle_Deg * PI / 180;
}
