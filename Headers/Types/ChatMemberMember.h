#ifndef TELEGRAM_TYPES_CHATMEMBERMEMBER_H
#define TELEGRAM_TYPES_CHATMEMBERMEMBER_H

#include "User.h"
#include "ChatMember.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a chat member that has no additional privileges or restrictions
     *
     */

    struct ChatMemberMember : public ChatMember
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatMemberMember();

        /** @brief Constructs ChatMemberMember object from parameters */
        ChatMemberMember(const User& user);

        /** @brief JSON constructor. Constructs ChatMemberMember object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatMemberMember class fields. For example it should contain pairs such as "user" = "...",
         * "status" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatMemberMember(const QJsonObject& jsonObject);

        /* @brief Returns ChatMemberMember in form of JSON object. Returns empty QJsonObject if ChatMemberMember is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if ChatMemberMember is empty */
        virtual bool isEmpty() const override;

 //** Fields **//

         /** @brief The member's status in the chat, always “member” */
        const QString status = "member";

        /** @brief Information about the user */
        User user;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBERMEMBER_H
