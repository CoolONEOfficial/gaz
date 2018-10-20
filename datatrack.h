#ifndef DATATRACK_H
#define DATATRACK_H

#include <vector>
#include <iostream>
#include <algorithm>
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

    void sort()
    {
        std::sort(points.begin(),points.end());
    }

    void print()
    {
        for(auto &p:points)
        {
            p.print();
        }
    }
};

#endif // DATATRACK_H