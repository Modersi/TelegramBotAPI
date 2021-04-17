#ifndef LOCATION_H
#define LOCATION_H

#include "Types/Type.h"

class Location : public Type
{
public:
    Location();

    Location(double longitude,
             double latitude);

    Location(QJsonObject jsonObject);

    double longitude();
    void   setLongitude(double longitude);

    double latitude();
    void   setLatitude(double latitude);
};

#endif // LOCATION_H
