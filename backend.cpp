#include "backend.h"
#include "datafull.h"
#include <string>
#include <fstream>
#include <clocale>

Backend::Backend(QObject *parent) :
    QObject(parent)
{
}

void Backend::test()
{
}

QVariant createVisualPoint(double lat, double lon)
{
    QVariant l;
    l.setValue(VisualPoint(lat, lon));
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

    VisualTrack tr;

    auto &points = datafull.vehicles["X9600000000000430"].points;

    for(int mPoint = 0; mPoint < 1000; mPoint++) {

        auto p = points[mPoint];
        double lat = p.latitude;
        double lon = p.longitude;
        std::cerr<<"lon=" << lon << " lat=" << lat << std::endl;
        tr.points << createVisualPoint(p.longitude, p.latitude);
    }

    //tr.points
//            << createVisualPoint(55.76880888888889, 37.499275555555556)
//            << createVisualPoint(56.33794666666667,
//    43.881080000000004)

   //         << createVisualPoint(56.33794666666667,
   // 43.881080000000004);
//            << createVisualPoint( 55.768813333333334, 37.499226666666665);
    doAddTrack(tr);
}
