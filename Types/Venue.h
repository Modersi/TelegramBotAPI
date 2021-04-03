#ifndef VENUE_H
#define VENUE_H

#include "Location.h"

class TELEGRAMAPI_EXPORT Venue : public Type
{
public:
    Venue();

    Venue(Location location,
          QString  title,
          QString  adress,
          QString  foursquareId = "",
          QString  foursquareType = "");

    Venue(QJsonObject jsonObject);

    Location location();
    void     setLocation(Location location);

    QString  title();
    void     setTitle(QString title);

    QString  adress();
    void     setAdress(QString adress);

    QString  foursquareId();
    void     setFoursquareId(QString foursquareId);
    bool     hasFoursquareId();

    QString  foursquareType();
    void     setFoursquareType(QString foursquareType);
    bool     hasFoursquareType();
};

#endif // VENUE_H
