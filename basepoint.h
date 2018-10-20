#ifndef BASEPOINT_H
#define BASEPOINT_H


class BasePoint
{
public:
    BasePoint();
    BasePoint(double m_latitude, double m_longitude);
    BasePoint(const BasePoint& bp);

public:
    double m_latitude;
    double m_longitude;
};

#endif // BASEPOINT_H
