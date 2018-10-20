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

    std::string fileList = "../../../../gaz/data/result/processed_files.txt";

    std::ofstream file("../../../../gaz/data/result/aaa.txt");
    file<<"test";
    file.close();


    datafull.process_all(fileList);
}
