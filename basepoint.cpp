#include "basepoint.h"

BasePoint::BasePoint()
{

}

BasePoint::BasePoint(double latitude, double longitude)
{
    this->m_latitude = latitude;
    this->m_longitude = longitude;
}

BasePoint::BasePoint(const BasePoint &bp)
    : BasePoint(bp.m_latitude, bp.m_longitude)
{

}
