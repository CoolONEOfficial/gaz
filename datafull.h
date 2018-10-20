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
                bool res = point.read(file);

                std::string vin = point.vin;

                vehicles[vin].addPoint(point);

                if( !res )
                {
                    std::cerr<<"=================";
                    break;
                }
                num++;
            }
        }

        std::cerr<<"====== num point="<<num<<std::endl;

        //printInfo();
        sortAll();

    }

    void process_all(const std::string& fileList)
    {
        std::string basePath = "/Users/valery/projects/gaz/gaz/data/result/";
        std::ifstream file(fileList);
        if (file)
        {
            std::string name;
            while(file >> name)
            {
                readFile(basePath + name);
            }

            printInfo();
        }
        else
        {
            qDebug("Can't open file list");
        }
   }
};

#endif // DATAFULL_H
