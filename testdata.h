#ifndef TESTDATA_H
#define TESTDATA_H

#include <fstream>


class TestData
{
public:
    double timestamp_S; // время, с
    double pitch_Rad; // тангаж, рад
    double roll_Rad; // крен, рад
    double heading_Rad; // курс, рад
    double latitude_Rad; // широта, рад
    double longitude_Rad; // долгота, рад
    double speed_MPerS; // модуль скорости, м/с
    double height_M; // высота, м
    double barometerHeight_M; // высота по барометру, м
    double fx_MPerS2, fy_MPerS2, fz_MPerS2, fzCompensated_MPerS2; // показания акселерометров, м/с^2
    double wx_RadPerS, wy_RadPerS, wz_RadPerS; // показания гироскопов, рад/с
    double ve_MPerS, vn_MPerS; // составляющие абсолютной скрости, м/с

    // качество сигнала GPS
    double gpsPDOP;
    double gpsHDOPP;
    double gpsVDOP;

    double gpsLatitude_Rad; // широта (по GPS), рад
    double gpsLongitude_Rad; // долгота (по GPS), рад
    double gpsHeight_M; // высота (по GPS), м
    double gpsSpeed_MPerS; // модуль скорости (по GPS), м/с
    double gpsHeading_Rad; // направление движения (по GPS), рад
    int gpsSatellitesNumber; // число спутников GPS

    std::ifstream dataFile;

    TestData(const char *fileName);
    ~TestData();
    bool updateData();
};

#endif // TESTDATA_H
