#ifndef TELEGRAM_TYPES_MESSAGEAUTODELETETIMERCHANGED_H
#define TELEGRAM_TYPES_MESSAGEAUTODELETETIMERCHANGED_H

#include <compare>

#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents the content of a service message, sent whenever a user in the chat triggers a proximity alert set by another user
     *
     */

    struct MessageAutoDeleteTimerChanged
    {
        /** @brief Default constructor. Constructs an empty MessageAutoDeleteTimerChanged object */
        MessageAutoDeleteTimerChanged();

        /** @brief Constructs MessageAutoDeleteTimerChanged object from parameters */
        MessageAutoDeleteTimerChanged(const qint32& message_auto_delete_time);

        /** @brief JSON constructor. Constructs MessageAutoDeleteTimerChanged object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "message_auto_delete_time" = "..." to construct correct object, otherwise empty object will be created */
        MessageAutoDeleteTimerChanged(const QJsonObject& json_object);


        /* @brief Returns MessageAutoDeleteTimerChanged in form of JSON object. Returns empty QJsonObject if MessageAutoDeleteTimerChanged is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if MessageAutoDeleteTimerChanged is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const MessageAutoDeleteTimerChanged&) const = default;


//** Fields **//

        /** @brief Unique message identifier */
        qint32 message_auto_delete_time;
    };
}

#endif // TELEGRAM_TYPES_MESSAGEAUTODELETETIMERCHANGED_H

