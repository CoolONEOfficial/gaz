#ifndef DATATRACK_H
#define DATATRACK_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "datapoint.h"
#include <QDateTime>
#include "valuepoint.h"

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
        int min = points[0].timestamp;
        int max = points[points.size()-1].timestamp;

        std::cerr<<"---------- Time delta="<<max-min<<std::endl;
    }

    void process_timestamps()
    {
        int maxDelta = -1;
        if( points.size() > 1 )
        {
            int prev = points[0].timestamp;
            int prevG = points[0].gps_timestamp;

            for( int k = 1; k < points.size(); k++ )
            {
                int curr = points[k].timestamp;
                int currG = points[k].gps_timestamp;
                int delta = curr - prev;
                int deltaG = currG - prevG;
                prev = curr;
                prevG = currG;

                int F = curr - currG;

                std::cerr<<"D="<<delta<<" G="<<deltaG<<" F="<<F<<"  time=";

                uint unixtimestamp = curr;

                QDateTime myDateTime;

                int req_id = points[k].req_id;
                myDateTime.setTime_t(unixtimestamp);
                QString str = myDateTime.toString("yyyy-MM-dd HH:mm:ss");
                std::cerr<<str.toStdString();
                std::cerr<<" req_id="<<req_id<<std::endl;
            }


        }

    }

    std::vector<ValuePoint> process_odometr()
    {
        std::vector<ValuePoint> result;
        if (points.size() > 1)
        {
            float prev_odometr = points[0].gps_odometer;
            float prev_fuel = points[0].can_fuel_level;

            for( int k = 0; k < points.size(); k++ )
            {
                float curr_fuel = points[k].can_fuel_level;
                float curr_odometr = points[k].gps_odometer;
                float delta_fuel = -(curr_fuel - prev_fuel);
                float delta_odometr = (curr_odometr - prev_odometr);
                if( delta_fuel != 0 )
                {
                    if( delta_fuel < 0 )
                    {// OK
                        //if( delta_odometr > 0 && delta_fuel < -10)
                        if( delta_odometr > 0 )
                        {
                            float rate = -100*(float)delta_fuel / (float)delta_odometr;
                            std::cerr<<"rate="<<rate
                                     <<" delta_fuel="<<delta_fuel
                                     <<" delta_odometr="<<delta_odometr
                                     <<" curr_odometr=" <<curr_odometr
                                     <<" curr_fuel=" << curr_fuel
                                     <<std::endl;

                            if( rate > 200)
                                rate = 200;
                            ValuePoint valuePoint;
                            valuePoint.timeStamp = points[k].timestamp;
                            valuePoint.value = rate;

                            result.push_back(valuePoint);


                            prev_odometr = curr_odometr;
                            prev_fuel = curr_fuel;
                        }
                    }
                    else if(delta_fuel > 10)
                    {// zapravka
                        std::cerr<<"------ Zapravka ---- F=" << delta_fuel
                                <<" prev_fuel=" << prev_fuel
                                <<" curr_fuel=" << curr_fuel
                                <<std::endl;
                        prev_odometr = curr_odometr;
                        prev_fuel = curr_fuel;
                    }


                }
            }

        }
        return result;
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
