#ifndef HELPER_H
#define HELPER_H

#include <map>
#include "matrix3x1.h"
#include "quaternion.h"


class Helper
{
public:
    // получить текущее время в секундах с момента запуска программы
    static double GetCurrentTime();

    // "интегрирование" производной за интервал времени
    static double Integrate(double derivative, double timeDelta, double constant);

    // расчет производной скорости Ve
    static double CalcVelocityEDerivative_MPerS2(double accelerationWFE_MPerS2, double latitude_Rad,
                                                 double omegaUp_1PerS, double velocityN_MPerS,
                                                 double velocityUp_MPerS, double omegaN_1PerS);
    // расчет производной скорости Vn
    static double CalcVelocityNDerivative_MPerS2(double accelerationWFN_MPerS2, double latitude_Rad,
                                                 double omegaUp_1PerS, double velocityE_MPerS,
                                                 double velocityUp_MPerS, double omegaE_1PerS);

    // эксцентриситет Земли
    static double EarthEccentricity();

    // экваториальный радиус Земли в метрах
    static double EarthEquatorialRadius_M();

    // радиусы Земли на заданной широте
    static double EarthPhiRadius_M(double latitude_Rad);
    static double EarthLambdaRadius_M(double latitude_Rad);

    // угловая скорость Земли
    static double EarthAngularSpeed_1PerS();

    // ускорение свободного падения
    static double AccelerationOfGravity_MPerS2(double latitude_Rad, double height_M);

    // расчет угловой скорости вращения СК (управляющий сигнал)
    static Matrix3x1 CalcAngularVelocityWF_RadPerS(double velocityN, double velocityE, double latitude_Rad, double height_M);

    // расчет линейной скорости СК
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

    // связанная - инерциальная СК
    static Quaternion CalcUpdatingQuaternion(Matrix3x1 omega_RadPerS, double timeDelta_S);

    // расчет углов ориентации
    static Matrix3x1 CalcOrientation_Rad(Quaternion q);

    // перевод градусов в радианы
    static double DegreesToRadians(double angle_Deg);
};

#endif // HELPER_H
