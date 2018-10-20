#include "visualpoint.h"

VisualPoint::VisualPoint()
{

}

VisualPoint::VisualPoint(const VisualPoint &parent)

{
    this->m_latitude = parent.getLatitude();
    this->m_longitude = parent.getLongitude();
}
