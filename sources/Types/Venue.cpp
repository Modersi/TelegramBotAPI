#include "Types/Venue.h"

Venue::Venue() {}

Venue::Venue(Location location,
             QString  title,
             QString  adress,
             QString  foursquareId,
             QString  foursquareType)
{
    _jsonObject.insert("location", QJsonValue(location.toObject()));
    _jsonObject.insert("title", QJsonValue(title));
    _jsonObject.insert("adress", QJsonValue(adress));

    if(!foursquareId.isEmpty())
        _jsonObject.insert("foursquare_id", QJsonValue(foursquareId));
    if(!foursquareType.isEmpty())
        _jsonObject.insert("foursquare_type", QJsonValue(foursquareType));
}

Venue::Venue(QJsonObject jsonObject)
{
    if(jsonObject.contains("location"))
        _jsonObject.insert("location", jsonObject.value("file_id"));

    if(jsonObject.contains("title"))
        _jsonObject.insert("title", jsonObject.value("title"));

    if(jsonObject.contains("adress"))
        _jsonObject.insert("adress", jsonObject.value("adress"));

    if(jsonObject.contains("foursquare_id"))
        _jsonObject.insert("foursquare_id", jsonObject.value("foursquare_id"));

    if(jsonObject.contains("foursquare_type"))
        _jsonObject.insert("foursquare_type", jsonObject.value("foursquare_type"));
}

// "get", "set" methods for "location" field //

Location Venue::location()
{
    return Location(_jsonObject.value("location").toObject());
}

void Venue::setLocation(Location location)
{
    _jsonObject.insert("location", location.toObject());
}

// "get", "set" methods for "title" field //

QString Venue::title()
{
    return _jsonObject.value("title").toString();
}

void Venue::setTitle(QString title)
{
    _jsonObject.insert("title", title);
}

// "get", "set" methods for "adress" field //

QString Venue::adress()
{
    return _jsonObject.value("adress").toString();
}

void Venue::setAdress(QString adress)
{
    _jsonObject.insert("adress", adress);
}

// "get", "set", "has" methods for "foursquare_id" field //

QString Venue::foursquareId()
{
    return _jsonObject.value("foursquare_id").toString();
}

void Venue::setFoursquareId(QString foursquareId)
{
    _jsonObject.insert("foursquare_id", foursquareId);
}

bool Venue::hasFoursquareId()
{
    return _jsonObject.contains("foursquare_id");
}

// "get", "set", "has" methods for "foursquare_type" field //

QString Venue::foursquareType()
{
    return _jsonObject.value("foursquare_type").toString();
}

void Venue::setFoursquareType(QString foursquareType)
{
    _jsonObject.insert("foursquare_type", foursquareType);
}

bool Venue::hasFoursquareType()
{
    return _jsonObject.contains("foursquare_type");
}
