#ifndef VISUALPOINT_H
#define VISUALPOINT_H

#include "QMetaType"
#include "basepoint.h"


class VisualPoint
{
    Q_GADGET
    Q_PROPERTY(double latitude READ getLatitude WRITE setLatitude )
    Q_PROPERTY(double longitude READ getLongitude WRITE setLongitude)
public:
    VisualPoint();
    VisualPoint(const VisualPoint& parent);
    VisualPoint(double lat, double lon) {setLatitude(lat); setLongitude(lon);}

    double m_latitude;
    double m_longitude;

    double getLatitude() const {return m_latitude;}
    double getLongitude() const {return m_longitude;}

    void setLatitude(const double lat) {m_latitude = lat;}
    void setLongitude(const double lon) {m_longitude = lon;}
};

Q_DECLARE_METATYPE(VisualPoint);

#endif // VISUALPOINT_H
