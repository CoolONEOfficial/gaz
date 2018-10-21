#ifndef VISUALTRACK_H
#define VISUALTRACK_H

#include <QMetaType>
#include "visualpoint.h"
#include <QVector>
#include <QVariantList>
#include <QColor>

class VisualTrack
{
    Q_GADGET
    Q_PROPERTY(QVariantList points READ getPoints WRITE setPoints )
    Q_PROPERTY(QColor color READ getColor WRITE setColor )
    Q_PROPERTY(QString vin READ getVin WRITE setVin )
public:
    VisualTrack();

    QVariantList points;

    QVariantList getPoints() {return points;}
    void setPoints(QVariantList p) {points = p;}

    QColor color;

    QColor getColor() {return color;}
    void setColor(QColor c) {color = c;}

    QString vin;

    QString getVin() {return vin;}
    void setVin(QString v) {vin = v;}
};

Q_DECLARE_METATYPE(VisualTrack);

#endif // VISUALTRACK_H
