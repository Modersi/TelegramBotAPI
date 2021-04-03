#include "Location.h"

Location::Location() {}

Location::Location(double longitude,
                   double latitude)
{
    _jsonObject.insert("longitude", QJsonValue(longitude));
    _jsonObject.insert("latitude", QJsonValue(latitude));
}

Location::Location(QJsonObject jsonObject)
{
    if(jsonObject.contains("longitude"))
        _jsonObject.insert("longitude", jsonObject.value("longitude"));

    if(jsonObject.contains("latitude"))
        _jsonObject.insert("latitude", jsonObject.value("latitude"));
}

double Location::longitude()
{
    return _jsonObject.value("longitude").toDouble();
}

void Location::setLongitude(double longitude)
{
    _jsonObject.insert("longitude", longitude);
}

double Location::latitude()
{
    return _jsonObject.value("latitude").toDouble();
}

void Location::setLatitude(double latitude)
{
    _jsonObject.insert("latitude", latitude);
}
