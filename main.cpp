#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "quaternion.h"
#include "matrix3x1.h"
#include "math.h"
#include "helper.h"
#include "testdata.h"
#include <iomanip>


int main()
{
    srand(time(NULL));

    // начальные условия
    TestData td("../../data.txt");
    if (!td.updateData())
        return 1;
    double countedTime_S = 0.01;
    Quaternion bodyWFQuaternion(1, 0, 0, 0);
    Matrix3x1 previousVelocityWF_MPerS(td.ve_MPerS, td.vn_MPerS, 0);
    Matrix3x1 previousAngularVelocityWF_RadPerS(0, 0, 0);
    double previousLatitude_Rad = td.latitude_Rad;
    double previousLongitude_Rad = td.longitude_Rad;
    double previousTimestamp_S = td.timestamp_S;
    double previousHeight_M = td.height_M;
    int stepToPrint = 0;
    const double k1 = 0.5;
    const double k2 = 0.5;
    const double kLatitude = 1;
    const double kLongitude = 1;
    const double c1 = 0.5;
    const double c2 = 0.5;

    while (true)
    {
        if (!td.updateData())
            return 2;

        countedTime_S += 0.01;
        if (countedTime_S < 600)
        {
            previousTimestamp_S = td.timestamp_S;
            continue;
        }

        Matrix3x1 angularVelocityBody_RadPerS(td.wx_RadPerS, td.wy_RadPerS, td.wz_RadPerS);
        Matrix3x1 accelerationBody_MPerS2(td.fx_MPerS2, td.fy_MPerS2, td.fzCompensated_MPerS2);

        Matrix3x1 accelerationWF_MPerS2 = bodyWFQuaternion.Transform(accelerationBody_MPerS2);

        // линейные скорости объекта и СК
        double timeDelta_S = td.timestamp_S - previousTimestamp_S;
        const double deltaHeight_M = previousHeight_M - td.gpsHeight_M;

        Matrix3x1 velocityWF_MPerS = Helper::CalcV_MPerS(accelerationWF_MPerS2, previousLatitude_Rad,
                                                         previousAngularVelocityWF_RadPerS, timeDelta_S,
                                                         previousVelocityWF_MPerS,
                                                         td.gpsSpeed_MPerS, td.heading_Rad, k1, k2,
                                                         c2, deltaHeight_M);

        // угловая скорость СК, компенсация GPS
        Matrix3x1 angularVelocityWF_RadPerS = Helper::CalcAngularVelocityWF_RadPerS(velocityWF_MPerS.N(),
                                                                                    velocityWF_MPerS.E(),
                                                                                    previousLatitude_Rad,
                                                                                    previousHeight_M);

        // производная от широты с компенсацией GPS
        const double deltaLatitude_Rad = previousLatitude_Rad - td.gpsLatitude_Rad;
        const double latitudeDerivative_RadPerS = -angularVelocityWF_RadPerS.N() - kLatitude * deltaLatitude_Rad;

        // широта
        const double latitude_Rad = Helper::Integrate(latitudeDerivative_RadPerS, timeDelta_S, previousLatitude_Rad);

        // производная от долготы с компенсацией GPS
        const double deltaLongitude_Rad = previousLongitude_Rad - td.gpsLongitude_Rad;
        double longitudeDerivative_RadPerS = (velocityWF_MPerS.E() /
                ((Helper::EarthLambdaRadius_M(latitude_Rad) + previousHeight_M) * cos(latitude_Rad))) -
                kLongitude * deltaLongitude_Rad;

        // долгота
        const double longitude_Rad = Helper::Integrate(longitudeDerivative_RadPerS, timeDelta_S,
                                                       previousLongitude_Rad);

        // пересчет МНК
        Quaternion updatingQuaternionBI = Helper::CalcUpdatingQuaternion(angularVelocityBody_RadPerS,
                                                                         timeDelta_S);
        Quaternion prelimQuaternion = updatingQuaternionBI.Transform(bodyWFQuaternion);

        Quaternion updatingQuaternionIN = Helper::CalcUpdatingQuaternion(angularVelocityWF_RadPerS,
                                                                         timeDelta_S);
        bodyWFQuaternion = prelimQuaternion.Transform(updatingQuaternionIN);

        // углы ориентации объекта
        Matrix3x1 bodyOrientation_Rad = Helper::CalcOrientation_Rad(bodyWFQuaternion);

        // высота
        const double heightDerivative = velocityWF_MPerS.Z() - c1 * deltaHeight_M;
        const double height_M = Helper::Integrate(heightDerivative, timeDelta_S, previousHeight_M);

        // подготовка к следующему шагу
        previousVelocityWF_MPerS = velocityWF_MPerS;
        previousLatitude_Rad = latitude_Rad;
        previousLongitude_Rad = longitude_Rad;
        previousAngularVelocityWF_RadPerS = angularVelocityWF_RadPerS;
        previousTimestamp_S = td.timestamp_S;
        previousHeight_M = height_M;
    }

    return 0;
}
