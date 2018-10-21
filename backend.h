#ifndef BACKEND_H
#define BACKEND_H

#include "datafull.h"
#include "visualtrack.h"

#include <QObject>
#include "datafull.h"
#include "graph.h"

class Backend : public QObject
{
    Q_OBJECT

    public:
        explicit Backend(QObject *parent = nullptr);

        Q_INVOKABLE void test();
        Q_INVOKABLE void onMapComplete();
        Q_INVOKABLE void onTimeSlider(int unixtimestamp);
        Q_INVOKABLE void onVinSelect(QString vin);
        Q_INVOKABLE void onVinSelectFuel(QString vin);

        QString selectedVin;

    DataFull datafull;

signals:
    void doAddTrack(VisualTrack vtrack);
    void doSwitchPoint(VisualPoint vpoint);
    void doDrawGraph(Graph graph);
};

#endif // BACKEND_H
