#ifndef TELEGRAM_TYPES_RESPONSEPARAMETERS_H
#define TELEGRAM_TYPES_RESPONSEPARAMETERS_H

#include <compare>
#include <optional>

#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief Contains information about why a request was unsuccessful
     * 
     */

    struct ResponseParameters
    {
        /** @brief Constructs ResponseParameters object from parameters */
        ResponseParameters(const std::optional<qint64>& migrate_to_chat_id = std::nullopt,
                           const std::optional<qint32>& retry_after = std::nullopt);

        /** @brief JSON constructor. Constructs ResponseParameters object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pairs related to ResponseParameters class, such as "migrate_to_chat_id" = "...", "retry_after" = "..." to construct correct
         * object, otherwise fields related to missing pairs will be setted to std::nullopt */
        ResponseParameters(const QJsonObject& json_object);


        /* @brief Returns ResponseParameters in form of JSON object. Returns empty QJsonObject if ResponseParameters is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ResponseParameters is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ResponseParameters&) const = default;


//** Fields **//

        /** @brief Optional. The group has been migrated to a supergroup with the specified identifier */
        std::optional<qint64> migrate_to_chat_id;
       
        /** @brief Optional. In case of exceeding flood control, the number of seconds left to wait before the request can be repeated */
        std::optional<qint32> retry_after;
    };
}

#endif // TELEGRAM_TYPES_RESPONSEPARAMETERS_H
