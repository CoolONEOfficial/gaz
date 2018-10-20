#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <fstream>
#include "basepoint.h"

class DataPoint: public BasePoint
{
public:
    void set(float lat, float lon)
    {
        latitude = lat;
        longitude = lon;
    }

    bool read(std::ifstream &file)
    {


    }
};

#endif // DATAPOINT_H
