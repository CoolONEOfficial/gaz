#include "backend.h"
#include "datafull.h"
#include <string>
#include <fstream>

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

    std::string fileList = "/home/coolone/gaz/data/result/processed_files.txt";

//    std::ofstream file("../../../../gaz/data/result/aaa.txt");
//    file<<"test";
//    file.close();

    datafull.process_all(fileList);

        VisualTrack tr;

    for(int mPoint = 0; mPoint < 3; mPoint++) {

        auto p = datafull.vehicles["X9600000000000430"].points[mPoint+1000];
        tr.points << createVisualPoint(p.longitude, p.latitude);
    }

    tr.points
//            << createVisualPoint(55.76880888888889, 37.499275555555556)
//            << createVisualPoint(56.33794666666667,
//    43.881080000000004)

            << createVisualPoint(56.33794666666667,
    43.881080000000004);
//            << createVisualPoint( 55.768813333333334, 37.499226666666665);
    doAddTrack(tr);
}
