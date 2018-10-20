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

    void readFile(const std::string &fileName)
    {
        std::fstream file(fileName);
        if (file)
        {
            DataPoint point;
            //point.read(file);
            std::string value;
            file >> value;
            qDebug(value.c_str());
        }
    }

    void process_all(const std::string& fileList)
    {
        std::string basePath = "/home/coolone/gaz/data/result/";
        std::ifstream file(fileList);
        if (file)
        {
            std::string name;
            while(file >> name)
            {
                qDebug(name.c_str());
                readFile(basePath + name);
            }
        }
        else
        {
            qDebug("Can't open file list");
        }
   }
};

#endif // DATAFULL_H
