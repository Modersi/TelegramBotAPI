#ifndef TELEGRAM_TYPES_LOCATION_H
#define TELEGRAM_TYPES_LOCATION_H

#include <compare>
#include <optional>

#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This object represents a point on the map
     *
     */

    struct Location
    {
        /** @brief Default constructor. Constructs an empty Location object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Location();

        /** @brief Constructs Location object from parameters */
        Location(const double& longitude,
                 const double& latitude,
                 const std::optional<double>& horizontal_accuracy = std::nullopt,
                 const std::optional<int>& live_period = std::nullopt,
                 const std::optional<int>& heading = std::nullopt,
                 const std::optional<int>& proximity_alert_radius = std::nullopt);

        /** @brief JSON constructor. Constructs Location object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Location class fields. For example it should contain pairs such as "longitude" = "...",
         * "latitude" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Location(const QJsonObject& json_object);


        /* @brief Returns Location in form of JSON object. Returns empty QJsonObject if Location is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Location is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Location&) const = default;


//** Fields **//

        /** @brief Longitude as defined by sender */
        double longitude;
        
        /** @brief Latitude as defined by sender */
        double latitude;
        
        /** @brief Optional. The radius of uncertainty for the location, measured in meters; 0 - 1500 */
        std::optional<double> horizontal_accuracy;
        
        /** @brief Optional. Time relative to the message sending date, during which the location can be updated, in seconds.For active live locations only */
        std::optional<int> live_period;
        
        /** @brief Optional. The direction in which user is moving, in degrees; 1 - 360. For active live locations only */
        std::optional<int> heading;
        
        /** @brief Optional. Maximum distance for proximity alerts about approaching another chat member, in meters.For sent live locations only */
        std::optional<int> proximity_alert_radius;
    };
}

#endif // TELEGRAM_TYPES_LOCATION_H
