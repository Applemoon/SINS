#ifndef TESTDATA_H
#define TESTDATA_H

#include <fstream>


class TestData
{
public:
    double timestamp_S; // �����, �
    double pitch_Rad; // ������, ���
    double roll_Rad; // ����, ���
    double heading_Rad; // ����, ���
    double latitude_Rad; // ������, ���
    double longitude_Rad; // �������, ���
    double speed_MPerS; // ������ ��������, �/�
    double height_M; // ������, �
    double barometerHeight_M; // ������ �� ���������, �
    double fx_MPerS2, fy_MPerS2, fz_MPerS2, fzCompensated_MPerS2; // ��������� ��������������, �/�^2
    double wx_RadPerS, wy_RadPerS, wz_RadPerS; // ��������� ����������, ���/�
    double ve_MPerS, vn_MPerS; // ������������ ���������� �������, �/�

    // �������� ������� GPS
    double gpsPDOP;
    double gpsHDOPP;
    double gpsVDOP;

    double gpsLatitude_Rad; // ������ (�� GPS), ���
    double gpsLongitude_Rad; // ������� (�� GPS), ���
    double gpsHeight_M; // ������ (�� GPS), �
    double gpsSpeed_MPerS; // ������ �������� (�� GPS), �/�
    double gpsHeading_Rad; // ����������� �������� (�� GPS), ���
    int gpsSatellitesNumber; // ����� ��������� GPS

    std::ifstream dataFile;

    TestData(const char *fileName);
    ~TestData();
    bool updateData();
};

#endif // TESTDATA_H
