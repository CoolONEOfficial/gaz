#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <fstream>
#include <QtDebug>
#include <string>
#include <vector>
#include <iostream>
#include "basepoint.h"


class DataPoint: public BasePoint
{
public:
    std::string vin;
    size_t timestamp;
    size_t gps_timestamp;

public:
    void set(float lat, float lon)
    {
        latitude = lat;
        longitude = lon;
    }

/*
-----------------------
0  Data:  deviceId
1  Data:  timestamp
2  Data:  req_id
3  Data:  res_id
4  Data:  event_id
5  Data:  vin
6  Data:  imei
7  Data:  gps.longitude
8  Data:  gpslatitude
9  Data:  gps.altitude
10  Data:  gps.course
11  Data:  gps.satellite_amount
12  Data:  gps.validity
13  Data:  gps.gpss_timestamp
14  Data:  gps.timestamp
15  Data:  gps.gsm_cell_monitor
16  Data:  gps.speed
17  Data:  gps.glonass_status
18  Data:  gps.acc_voltage
19  Data:  gps.ingition_status
20  Data:  gps.power_status
21  Data:  gps.airbag_fired
22  Data:  gps.odometer
23  Data:  gps.errorCodes
24  Data:  can.speed
25  Data:  can.remaining_mileage
26  Data:  can.fuel_level
27  Data:  can.fuel_consumption
28  Data:  can.coolant_temp
29  Data:  can.engine_oil_pressure
30  Data:  can.onboard_power_voltage
31  Data:  can.coolant_level_low
32  Data:  can.generator_malfunction
33  Data:  can.break_fluid_low_level
34  Data:  can.max_rpm
-----------------------

*/
    void print()
    {
        std::cerr<<"lat="<<latitude<<"="<<std::endl;
        std::cerr<<"lon="<<longitude<<"="<<std::endl;
        std::cerr<<"vin="<<vin<<"="<<std::endl;
        std::cerr<<"time_stamp="<<timestamp<<std::endl;
        std::cerr<<"gps_timestamp"<<gps_timestamp<<std::endl;

    }

    bool operator<(const DataPoint& other) const
    {
        return timestamp < other.timestamp;
    }

    int read(std::ifstream &file)
    {
        //qDebug("-----Point-------");

        std::vector<std::string> lines(35);


        for( int k = 0; k < 35; k++ )
        {
            std::getline(file, lines[k]);
            if( k==0 && lines[0].empty() )
                return -1;


            // qDebug(lines[k].c_str());
        }

        for(auto s: lines)
        {
            //qDebug(s.c_str());
        }

        //std::cerr<<"LAT="<<lines[7]<<std::endl;
        //std::cerr<<"LON="<<lines[8]<<std::endl;

        latitude = std::stod(lines[7]);
        longitude = std::stod(lines[8]);
        vin = lines[5];
        timestamp = std::stoi(lines[1]);
        gps_timestamp = std::stoi(lines[14]);

        if( latitude > 100 || longitude > 100 )
            return 0;
        //print();
        //std::cout<<"hello bbb";

        //qDebug("lat=", lat, " lon=", lon);



        //qDebug("-------------------");
        return 1;



    }
};

#endif // DATAPOINT_H
