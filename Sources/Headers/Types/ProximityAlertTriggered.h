#ifndef TELEGRAM_TYPES_PROXIMITYALERTTRIGGERED_H
#define TELEGRAM_TYPES_PROXIMITYALERTTRIGGERED_H

#include <compare>

#include "qjsonobject.h"

#include "User.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents the content of a service message, sent whenever a user in the chat triggers a proximity alert set by another user
     *
     */

    struct ProximityAlertTriggered
    {
        /** @brief Default constructor. Constructs an empty ProximityAlertTriggered object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ProximityAlertTriggered();

        /** @brief Constructs ProximityAlertTriggered object from parameters */
        ProximityAlertTriggered(const User& traveler,
                                const User& watcher,
                                const qint32& distance);

        /** @brief JSON constructor. Constructs ProximityAlertTriggered object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ProximityAlertTriggered class fields. For example it should contain pairs such as "traveler" = "...",
         * "watcher" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ProximityAlertTriggered(const QJsonObject& json_object);


        /* @brief Returns ProximityAlertTriggered in form of JSON object. Returns empty QJsonObject if ProximityAlertTriggered is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ProximityAlertTriggered is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ProximityAlertTriggered&) const = default;


//** Fields **//

        /** @brief User that triggered the alert */
        User traveler;

        /** @brief User that set the alert */
        User watcher;

        /** @brief The distance between the users */
        qint32 distance;
    };
}

#endif // TELEGRAM_TYPES_PROXIMITYALERTTRIGGERED_H

