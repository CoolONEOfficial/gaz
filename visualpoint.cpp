#include "visualpoint.h"

VisualPoint::VisualPoint()
{

}

VisualPoint::VisualPoint(const VisualPoint &parent)

{
    this->m_latitude = parent.getLatitude();
    this->m_longitude = parent.getLongitude();
    this->timestamp = parent.getTimestamp();
}

VisualPoint::VisualPoint(double lat, double lon, int ts)
{
    setLatitude(lat);
    setLongitude(lon);
    setTimestamp(ts);
}
