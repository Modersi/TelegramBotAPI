#ifndef TELEGRAM_TYPES_VENUE_H
#define TELEGRAM_TYPES_VENUE_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "Location.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a venue
     * 
     */

    struct Venue
    {
        /** @brief Default constructor. Constructs an empty Venue object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        Venue();

        /** @brief Constructs Venue object from parameters */
        Venue(const Location& location,
              const QString& title,
              const QString& address,
              const std::optional<QString>& foursquare_id = std::nullopt,
              const std::optional<QString>& foursquare_type = std::nullopt,
              const std::optional<QString>& google_place_id = std::nullopt,
              const std::optional<QString>& google_place_type = std::nullopt);

        /** @brief JSON constructor. Constructs Venue object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to Venue class fields. For example it should contain pairs such as "location" = "...",
         * "title" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        Venue(const QJsonObject& json_object);


        /* @brief Returns Venue in form of JSON object. Returns empty QJsonObject if Venue is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if Venue is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const Venue&) const = default;


//** Fields **//

        /** @brief Venue location. Can't be a live location */
        Location location;
        
        /** @brief Name of the venue */
        QString title;
        
        /** @brief Address of the venue */
        QString address;
        
        /** @brief Optional. Foursquare identifier of the venue */
        std::optional<QString> foursquare_id;
        
        /** @brief Optional. Foursquare type of the venue. (For example, “arts_entertainment / default”, “arts_entertainment / aquarium” or “food / icecream”.) */
        std::optional<QString> foursquare_type;
        
        /** @brief Optional. Google Places identifier of the venue */
        std::optional<QString> google_place_id;
        
        /** @brief Optional.Google Places type of the venue. (See [supported types](https://developers.google.com/places/web-service/supported_types)) */
        std::optional<QString> google_place_type;
    };
}

#endif // TELEGRAM_TYPES_VENUE_H
