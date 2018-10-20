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
    qDebug("tesatda");

    DataFull datafull;

    std::string fileList = "/home/coolone/gaz/data/result/processed_files.txt";

//    std::ofstream file("../../../../gaz/data/result/aaa.txt");
//    file<<"test";
//    file.close();


    datafull.process_all(fileList);
}

QVariant createVisualPoint(double lat, double lon)
{
    QVariant l;
    l.setValue(VisualPoint(lat, lon));
    return l;
}

void Backend::onMapComplete()
{

    VisualTrack tr;
    tr.points
            << createVisualPoint(55.76880888888889, 37.499275555555556)
            << createVisualPoint(55.76880888888889, 37.499275555555556)
            << createVisualPoint( 55.768813333333334, 37.499226666666665);
    doAddTrack(tr);
}
