#ifndef BACKEND_H
#define BACKEND_H

#include "datafull.h"
#include "visualtrack.h"

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT

    public:
        explicit Backend(QObject *parent = nullptr);

        Q_INVOKABLE void test();
        Q_INVOKABLE void onMapComplete();
        Q_INVOKABLE void onTimeSlider(int unixtimestamp);

    DataFull datafull;

signals:
    void doAddTrack(VisualTrack vtrack);
    void doSwitchPoint(VisualPoint vpoint);
};

#endif // BACKEND_H
