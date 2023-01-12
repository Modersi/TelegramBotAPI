#ifndef TELEGRAM_TYPES_VOICECHATPARTICIPANTSINVITED_H
#define TELEGRAM_TYPES_VOICECHATPARTICIPANTSINVITED_H

#include <compare>

#include "qvector.h"
#include "qjsonobject.h"

#include "User.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a service message about a voice chat scheduled in the chat
     *
     */

    struct VoiceChatParticipantsInvited
    {
        /** @brief Default constructor. Constructs an empty VoiceChatScheduled object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        VoiceChatParticipantsInvited();

        /** @brief Constructs VoiceChatScheduled object from parameters */
        VoiceChatParticipantsInvited(const QVector<User>& users);

        /** @brief JSON constructor. Constructs VoiceChatScheduled object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has key-value pair "users" = "..." to contruct correct object, otherwise empty object will be created */
        VoiceChatParticipantsInvited(const QJsonObject& json_object);


        /** @brief Returns VoiceChatParticipantsInvited in form of JSON object. Returns empty QJsonObject if VoiceChatParticipantsInvited is empty */
        QJsonObject toObject() const;

        /** @brief Returns true if VoiceChatParticipantsInvited is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const VoiceChatParticipantsInvited&) const = default;


//** Fields **//

        /** @brief This struct represents a service message about new members invited to a voice chat */
        QVector<User> users;
    };
}

#endif // TELEGRAM_TYPES_VOICECHATPARTICIPANTSINVITED_H

