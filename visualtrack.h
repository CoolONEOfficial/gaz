#ifndef VISUALTRACK_H
#define VISUALTRACK_H

#include <QMetaType>
#include "visualpoint.h"
#include <QVector>
#include <QVariantList>

class VisualTrack
{
    Q_GADGET
    Q_PROPERTY(QVariantList points READ getPoints WRITE setPoints )
public:
    VisualTrack();

    QVariantList points;

    QVariantList getPoints() {return points;}
    void setPoints(QVariantList p) {points = p;}
};

Q_DECLARE_METATYPE(VisualTrack);

#endif // VISUALTRACK_H
