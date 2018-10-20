#include "basepoint.h"

BasePoint::BasePoint()
{

}

BasePoint::BasePoint(double latitude, double longitude)
{
    this->latitude = latitude;
    this->longitude = longitude;
}

BasePoint::BasePoint(const BasePoint &bp)
    : BasePoint(bp.latitude, bp.longitude)
{

}
