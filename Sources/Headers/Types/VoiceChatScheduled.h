#ifndef TELEGRAM_TYPES_VOICECHATSCHEDULED_H
#define TELEGRAM_TYPES_VOICECHATSCHEDULED_H

#include <compare>

#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a service message about a voice chat scheduled in the chat
     *
     */

    struct VoiceChatScheduled
    {
        /** @brief Default constructor. Constructs an empty VoiceChatScheduled object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        VoiceChatScheduled();

        /** @brief Constructs VoiceChatScheduled object from parameters */
        VoiceChatScheduled(const qint32& start_date);

        /** @brief JSON constructor. Constructs VoiceChatScheduled object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "start_date" = "..." to contruct correct object, otherwise empty object will be created */
        VoiceChatScheduled(const QJsonObject& json_object);


        /** @brief Returns VoiceChatScheduled in form of JSON object. Returns empty QJsonObject if VoiceChatScheduled is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if VoiceChatScheduled is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const VoiceChatScheduled&) const = default;


//** Fields **//

        /** @brief Point in time (Unix timestamp) when the voice chat is supposed to be started by a chat administrator */
        qint32 start_date;
    };
}

#endif // TELEGRAM_TYPES_VOICECHATSCHEDULED_H

