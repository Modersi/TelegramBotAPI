#ifndef TELEGRAM_TYPES_VOICECHATSTARTED_H
#define TELEGRAM_TYPES_VOICECHATSTARTED_H

#include <compare>

#include "qjsonobject.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a service message about a voice chat started in the chat. Currently holds no information
     *
     */

    struct VoiceChatStarted
    {
        VoiceChatStarted();


        /** @brief Returns VoiceChatStarted in form of JSON object. Returns empty QJsonObject if VoiceChatStarted is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if VoiceChatStarted is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const VoiceChatStarted&) const = default;

    };
}

#endif // TELEGRAM_TYPES_VOICECHATSTARTED_H

