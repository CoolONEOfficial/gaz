#include "backend.h"
#include "datafull.h"
#include <string>
#include <fstream>
#include <clocale>
#include <QRandomGenerator>
#include <array>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;

Backend::Backend(QObject *parent) :
    QObject(parent)
{
}

void Backend::test()
{
}

QVariant createVisualPoint(double lat, double lon, int timestamp)
{
    QVariant l;
    VisualPoint vp = VisualPoint(lat, lon, timestamp);
    l.setValue(vp);
    return l;
}

void Backend::onMapComplete()
{
    qDebug("tesatda");

#ifndef __APPLE__
    std::string fileList = "/home/coolone/gaz/data/result/processed_files.txt";
#else
    std::string fileList = "/Users/valery/projects/gaz/gaz/data/result/processed_files.txt";
#endif
//    std::ofstream file("../../../../gaz/data/result/aaa.txt");
//    file<<"test";
//    file.close();

    std::setlocale(LC_ALL, "C");

    datafull.process_all(fileList);

    return;

    for(auto mVehicle: { *datafull.vehicles.begin()}) {
        VisualTrack tr;

        static std::array<QColor, 5> colors = {Qt::black, Qt::red, Qt::gray, Qt::green, Qt::blue};

        tr.setColor(colors[rand() % colors.size()]);
        tr.setVin(QString::fromStdString(mVehicle.first));


        int num = 5000;
        for(auto mPoint: mVehicle.second.points) {
//            double lat = mPoint.latitude;
//            double lon = mPoint.longitude;
            //std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
            tr.points << createVisualPoint( mPoint.latitude, mPoint.longitude, mPoint.timestamp);
            num--;
            if(num<0)
                break;
        }

        doAddTrack(tr);
    }

    std::cerr<<"--------- Finish add points"<<std::endl;


//    auto &points = datafull.vehicles["X9600000000000430"].points;

//    for(int mPoint = 0; mPoint < 1000; mPoint++) {

//        auto p = points[mPoint];
//        double lat = p.latitude;
//        double lon = p.longitude;
//        std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
//        tr.points << createVisualPoint(p.longitude, p.latitude);
//    }


    //doAddTrack(tr);


    std::cerr<<"--------- Finish doAddTrack"<<std::endl;

    VisualTrack tr2;

    auto &points2 = datafull.vehicles["X9600000000000225"].points;

    for(int mPoint = 0; mPoint < 5000; mPoint++) {

        auto p = points2[mPoint];
//        double lat = p.latitude;
//        double lon = p.longitude;

        //std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
        tr2.points << createVisualPoint( p.latitude,p.longitude, p.timestamp);
    }

    std::cerr<<"--------- Finish add points2"<<std::endl;


    doAddTrack(tr2);

    VisualTrack tr3;

    auto &points3 = datafull.vehicles["X9600000000000068"].points;

    for(int mPoint = 0; mPoint < 5000; mPoint++) {

        auto p = points3[mPoint];
        //double lat = p.latitude;
        //double lon = p.longitude;
        //std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
        tr3.points << createVisualPoint( p.latitude,p.longitude, p.timestamp);
    }

    std::cerr<<"--------- Finish add points3"<<std::endl;

    doAddTrack(tr3);

}

void Backend::onTimeSlider(int unixtimestamp)
{
    std::cerr<<"---------- onTimeSlider" <<std::endl;

    //or(auto mVehicle: { *datafull.vehicles.begin()})
    {
        if(selectedVin.length() == 0)
            return;

        auto mVehicle = datafull.vehicles[selectedVin.toStdString()];

        auto &mPoints = mVehicle.points;
        auto lowPoint = DataPoint();
        lowPoint.timestamp = unixtimestamp;
        auto lower = std::lower_bound(mPoints.begin(), mPoints.end(), lowPoint);
        std::cerr<<"unixtimestamp="<<unixtimestamp<<std::endl;
        if(lower != mPoints.end())
        {
            std::cerr<<"---------- Found"<<std::endl;
            std::cerr<<"lat="<<lower->latitude
                     <<"lon="<<lower->longitude<<std::endl;
            doSwitchPoint(VisualPoint(   lower.base()->latitude, lower.base()->longitude,  lower.base()->timestamp));
        }
        else
        {
            std::cerr<<"------- Not found"<<std::endl;
        }
    }
}

void Backend::onVinSelect(QString vin)
{
    selectedVin = vin;
    std::cerr<<"---------- onVinSelect" << vin.toStdString()<<std::endl;

    VisualTrack tr3;

    auto &points3 = datafull.vehicles[vin.toStdString()].points;

    for(int mPoint = 0; mPoint < 5000; mPoint++) {

        auto p = points3[mPoint];
        //double lat = p.latitude;
        //double lon = p.longitude;
        //std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
        tr3.points << createVisualPoint(p.latitude, p.longitude, p.timestamp);
    }

    std::cerr<<"--------- Finish add points3"<<std::endl;

    doAddTrack(tr3);

}

