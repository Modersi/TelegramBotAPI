#ifndef TELEGRAM_TYPES_CHATMEMBERLEFT_H
#define TELEGRAM_TYPES_CHATMEMBERLEFT_H

#include <compare>

#include "qjsonobject.h"

#include "User.h"
#include "ChatMember.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a chat member that isn't currently a member of the chat, but may join it themselves
     *
     */

    struct ChatMemberLeft : public ChatMember
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatMemberLeft();

        /** @brief Constructs ChatMemberLeft object from parameters */
        ChatMemberLeft(const User& user);

        /** @brief JSON constructor. Constructs ChatMemberLeft object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatMemberLeft class fields. For example it should contain pairs such as "user" = "...",
         * "status" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatMemberLeft(const QJsonObject& json_object);


        /* @brief Returns ChatMemberLeft in form of JSON object. Returns empty QJsonObject if ChatMemberLeft is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if ChatMemberLeft is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns status of the ChatMember */
        virtual Status getStatus() const override;


        std::partial_ordering operator <=> (const ChatMemberLeft&) const = default;


//** Fields **//

        /** @brief The member's status in the chat, always “left” */
        const Status status = Status::LEFT;

        /** @brief Information about the user */
        User user;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBERLEFT_H
