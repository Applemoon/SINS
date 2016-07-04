#include "testdata.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "helper.h"
#include <cmath>


TestData::TestData(const char* fileName)
{
    dataFile.open(fileName);
    if (!dataFile.is_open())
        std::cout << "Unable to open file\n";
}


TestData::~TestData()
{
    dataFile.close();
}


bool TestData::updateData()
{
    std::string line;
    if (!dataFile.is_open() || !getline(dataFile, line))
        return false;

    std::vector<double> elems;
    std::stringstream ss(line);
    std::string item;
    while (getline(ss, item, ' '))
    {
        char* elemChar = const_cast<char*>(item.c_str());
        double elemDouble = atof(elemChar);
        elems.push_back(elemDouble);
    }

    timestamp_S = elems[0] / 100;
    pitch_Rad = Helper::DegreesToRadians(elems[1]);
    roll_Rad = Helper::DegreesToRadians(elems[2]);
//    double intpart;
//    heading_Rad = modf(Helper::DegreesToRadians(elems[3]), &intpart);
    heading_Rad = Helper::DegreesToRadians(elems[3]);
    latitude_Rad = Helper::DegreesToRadians(elems[4]);
    longitude_Rad = Helper::DegreesToRadians(elems[5]);
    speed_MPerS = elems[6];
    height_M = elems[7];
    barometerHeight_M = elems[8];
    fx_MPerS2 = elems[9];
    fy_MPerS2 = elems[10];
    fz_MPerS2 = elems[11];
    wx_RadPerS = Helper::DegreesToRadians(elems[12]);
    wy_RadPerS = Helper::DegreesToRadians(elems[13]);
    wz_RadPerS = Helper::DegreesToRadians(elems[14]);
    ve_MPerS = elems[15];
    vn_MPerS = elems[16];
    gpsPDOP = elems[17];
    gpsHDOPP = elems[18];
    gpsVDOP = elems[19];
    gpsLatitude_Rad = Helper::DegreesToRadians(elems[20]);
    gpsLongitude_Rad = Helper::DegreesToRadians(elems[21]);
    gpsHeight_M = elems[22];
    gpsSpeed_MPerS = elems[23];
    gpsHeading_Rad = Helper::DegreesToRadians(elems[24]);
    gpsSatellitesNumber = elems[25];

    fzCompensated_MPerS2 = fz_MPerS2 - Helper::AccelerationOfGravity_MPerS2(latitude_Rad, height_M);
    return true;
}
