#ifndef TELEGRAM_TYPES_VOICECHATENDED_H
#define TELEGRAM_TYPES_VOICECHATENDED_H

#include "qstring.h"
class QJsonObject;

namespace Telegram
{
    /**
     *
     * @brief This struct represents a service message about a voice chat ended in the chat
     *
     */

    struct VoiceChatEnded
    {
        /** @brief Default constructor. Constructs an empty VoiceChatEnded object */
        VoiceChatEnded();

        /** @brief Constructs VoiceChatEnded object from parameters */
        VoiceChatEnded(const qint32& duration);

        /** @brief JSON constructor. Constructs VoiceChatEnded object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "duration" = "..." to contruct correct object, otherwise empty object will be created */
        VoiceChatEnded(const QJsonObject& jsonObject);

        /** @brief Returns VoiceChatEnded in form of JSON object. Returns empty QJsonObject if VoiceChatEnded is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if VoiceChatEnded is empty */
        bool isEmpty() const;

//** Fields **//

        /** @brief Voice chat duration; in seconds */
        qint32 duration;
    };
}

#endif // TELEGRAM_TYPES_VOICECHATENDED_H

