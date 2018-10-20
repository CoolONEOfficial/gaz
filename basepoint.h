#ifndef BASEPOINT_H
#define BASEPOINT_H


class BasePoint
{
public:
    BasePoint();
    BasePoint(double latitude, double longitude);
    BasePoint(const BasePoint& bp);

public:
    double latitude;
    double longitude;
};

#endif // BASEPOINT_H
