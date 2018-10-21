#ifndef BACKEND_H
#define BACKEND_H

#include "visualtrack.h"

#include <QObject>
#include "datafull.h"

class Backend : public QObject
{
    Q_OBJECT

    public:
        DataFull datafull;

        explicit Backend(QObject *parent = nullptr);

        Q_INVOKABLE void test();
        Q_INVOKABLE void onMapComplete();
        Q_INVOKABLE void onTimeSlider(int unixtimestamp);
        Q_INVOKABLE void onVinSelect(QString vin);


signals:
    void doAddTrack(VisualTrack vtrack);
    void doAddPoint(VisualPoint vpoint);
};

#endif // BACKEND_H
