#ifndef DATAFULL_H
#define DATAFULL_H

#include <map>
#include <string>
#include <fstream>
#include "datatrack.h"
#include "datapoint.h"
#include <QDebug>

class DataFull
{
public:
    DataFull();

    std::map<std::string, DataTrack> vehicles;

    void printInfo()
    {
        for( auto &vin: vehicles)
        {
            int num = vin.second.points.size();
            std::cerr << "vin=" << vin.first << " num=" << num << std::endl;
            //vin.second.print();
        }
    }

    void sortAll()
    {
        for( auto &vin: vehicles)
        {
            std::cerr<<"---------------Start sort"<<std::endl;
            vin.second.sort();
            std::cerr<<"---------------End sort"<<std::endl;
        }
    }

    void readFile(const std::string &fileName)
    {
        std::ifstream file(fileName);
        int num = 0;
        if (file)
        {
            for(;;)
            //for(int k = 0; k < 20; k++)
            {
                DataPoint point;
                int res = point.read(file);

                std::string vin = point.vin;


                if( res < 0 )
                {
                    std::cerr<<"=================";
                    break;
                }

                if(res > 0)
                {
                    vehicles[vin].addPoint(point);
                }
                num++;
            }
        }

        std::cerr<<"====== num point="<<num<<std::endl;

        //printInfo();


    }

    void process_all_timestamps()
    {
        for( auto &vin: vehicles)
        {
            vin.second.process_timestamps();
        }
    }

    void process_all_odometr()
    {
        for( auto &vin: vehicles )
        {
            auto result = vin.second.process_odometr();
        }
    }

    void process_all(const std::string& fileList)
    {
#ifndef __APPLE__
        std::string basePath = "/home/coolone/gaz/data/result/";
#else
        std::string basePath = "/Users/valery/projects/gaz/gaz/data/result/";
#endif
        std::ifstream file(fileList);
        if (file)
        {
            std::string name;
            while(file >> name)
            {
                readFile(basePath + name);
            }

            printInfo();
            sortAll();
            //process_all_timestamps();
            process_all_odometr();
        }
        else
        {
            qDebug("Can't open file list");
        }
   }
};

#endif // DATAFULL_H
