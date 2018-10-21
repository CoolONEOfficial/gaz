#ifndef VISUALPOINT_H
#define VISUALPOINT_H

#include "QMetaType"

class VisualPoint
{
    Q_GADGET
    Q_PROPERTY(double latitude READ getLatitude WRITE setLatitude )
    Q_PROPERTY(double longitude READ getLongitude WRITE setLongitude)
    Q_PROPERTY(int timestamp READ getTimestamp WRITE setTimestamp)
public:
    VisualPoint();
    VisualPoint(const VisualPoint& parent);
    VisualPoint(double lat, double lon, int ts);

    double m_latitude;
    double m_longitude;

    int timestamp;

    double getLatitude() const {return m_latitude;}
    double getLongitude() const {return m_longitude;}
    int getTimestamp() const {return timestamp;}

    void setLatitude(const double lat) {m_latitude = lat;}
    void setLongitude(const double lon) {m_longitude = lon;}
    void setTimestamp(const int ts) {timestamp = ts;}

};

Q_DECLARE_METATYPE(VisualPoint);

#endif // VISUALPOINT_H
