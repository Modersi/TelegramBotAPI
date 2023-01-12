#ifndef TELEGRAM_TYPES_CHATLOCATION_H
#define TELEGRAM_TYPES_CHATLOCATION_H

#include <compare>

#include "qjsonobject.h"
#include "qstring.h"

#include "Location.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a location to which a chat is connected
     *
     */

    struct ChatLocation
    {
        /** @brief Default constructor. Constructs an empty ChatLocation object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatLocation();

        /** @brief Constructs ChatLocation object from parameters */
        ChatLocation(const Location& location,
                     const QString& address);

        /** @brief JSON constructor. Constructs ChatLocation object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatLocation class fields. For example it should contain pairs such as "location" = "...",
         * "address" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatLocation(const QJsonObject& json_object);


        /* @brief Returns ChatLocation in form of JSON object. Returns empty QJsonObject if ChatLocation is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ChatLocation is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ChatLocation&) const = default;


//** Fields **//

        /** @brief The location to which the supergroup is connected. Can't be a live location */
        Location location;

        /** @brief Location address; 1-64 characters, as defined by the chat owner */
        QString address;
    };
}

#endif // TELEGRAM_TYPES_CHATLOCATION_H

