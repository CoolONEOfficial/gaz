#ifndef DATATRACK_H
#define DATATRACK_H

#include <vector>
#include "datapoint.h"

class DataTrack
{
public:
    DataTrack();
    std::vector<DataPoint> points;

    void addPoint(const DataPoint &newPoint)
    {
        points.push_back(newPoint);
    }
};

#endif // DATATRACK_H
