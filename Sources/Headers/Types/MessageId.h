#ifndef TELEGRAM_TYPES_MESSAGEID_H
#define TELEGRAM_TYPES_MESSAGEID_H

#include <compare>

#include "qstring.h"
class QJsonObject;

namespace Telegram
{
    /**
     *
     * @brief This struct represents a unique message identifier
     *
     */

    struct MessageId
    {
        /** @brief Default constructor. Constructs an empty MessageId object */
        MessageId();

        /** @brief Constructs MessageId object from parameters */
        MessageId(const qint32& message_id);

        /** @brief JSON constructor. Constructs MessageId object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "message_id" = "..." to contruct correct object, otherwise empty object will be created */
        MessageId(const QJsonObject& json_object);

        /* @brief Returns MessageId in form of JSON object. Returns empty QJsonObject if MessageId is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if MessageId is empty */
        bool isEmpty() const;

        std::partial_ordering operator <=> (const MessageId&) const = default;

//** Fields **//

        /** @brief Unique message identifier */
        qint32 message_id;
    };
}

#endif // TELEGRAM_TYPES_VOICE_H

