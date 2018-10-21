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

    DataFull datafull;

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

    for(auto mVehicle: { *datafull.vehicles.begin()}) {
        VisualTrack tr;

        static std::array<QColor, 5> colors = {Qt::black, Qt::red, Qt::gray, Qt::green, Qt::blue};

        tr.setColor(colors[rand() % colors.size()]);
        tr.setVin(QString::fromStdString(mVehicle.first));

<<<<<<< HEAD
    for(int mPoint = 0; mPoint < 500; mPoint++) {

        auto p = points[mPoint];
        double lat = p.latitude;
        double lon = p.longitude;
        //std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
        tr.points << createVisualPoint(p.longitude, p.latitude);
    }

    std::cerr<<"--------- Finish add points"<<std::endl;
=======
        for(auto mPoint: mVehicle.second.points) {
//            double lat = mPoint.latitude;
//            double lon = mPoint.longitude;
            //std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
            tr.points << createVisualPoint(mPoint.longitude, mPoint.latitude, mPoint.timestamp);
        }

        doAddTrack(tr);
    }

//    auto &points = datafull.vehicles["X9600000000000430"].points;

//    for(int mPoint = 0; mPoint < 1000; mPoint++) {

//        auto p = points[mPoint];
//        double lat = p.latitude;
//        double lon = p.longitude;
//        std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
//        tr.points << createVisualPoint(p.longitude, p.latitude);
//    }
>>>>>>> 1dfd1e9dded31c9824e8e55984d4550dcc6e99fe

    //tr.points
//            << createVisualPoint(55.76880888888889, 37.499275555555556)
//            << createVisualPoint(56.33794666666667,
//    43.881080000000004)

   //         << createVisualPoint(56.33794666666667,
   // 43.881080000000004);
//            << createVisualPoint( 55.768813333333334, 37.499226666666665);

<<<<<<< HEAD

    doAddTrack(tr);


    std::cerr<<"--------- Finish doAddTrack"<<std::endl;

    VisualTrack tr2;

    auto &points2 = datafull.vehicles["X9600000000000225"].points;

    for(int mPoint = 0; mPoint < 500; mPoint++) {

        auto p = points2[mPoint];
        double lat = p.latitude;
        double lon = p.longitude;
        //std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
        tr2.points << createVisualPoint(p.longitude, p.latitude);
    }

    std::cerr<<"--------- Finish add points2"<<std::endl;


    doAddTrack(tr2);

    VisualTrack tr3;

    auto &points3 = datafull.vehicles["X9600000000000068"].points;

    for(int mPoint = 0; mPoint < 500; mPoint++) {

        auto p = points3[mPoint];
        double lat = p.latitude;
        double lon = p.longitude;
        //std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
        tr3.points << createVisualPoint(p.longitude, p.latitude);
    }

    std::cerr<<"--------- Finish add points3"<<std::endl;


    doAddTrack(tr3);


=======
>>>>>>> 1dfd1e9dded31c9824e8e55984d4550dcc6e99fe
}
