#ifndef TELEGRAM_TYPES_CHATMEMBERBANNED_H
#define TELEGRAM_TYPES_CHATMEMBERBANNED_H

#include <compare>

#include "qjsonobject.h"

#include "User.h"
#include "ChatMember.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a chat member that was banned in the chat and can't return to the chat or view chat messages
     *
     */

    struct ChatMemberBanned : public ChatMember
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatMemberBanned();

        /** @brief Constructs ChatMemberBanned object from parameters */
        ChatMemberBanned(const User& user, const qint32& until_date);

        /** @brief JSON constructor. Constructs ChatMemberBanned object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatMemberBanned class fields. For example it should contain pairs such as "user" = "...",
         * "status" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatMemberBanned(const QJsonObject& json_object);


        /* @brief Returns ChatMemberBanned in form of JSON object. Returns empty QJsonObject if ChatMemberBanned is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if ChatMemberBanned is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns status of the ChatMember */
        virtual Status getStatus() const override;


        std::partial_ordering operator <=> (const ChatMemberBanned&) const = default;


//** Fields **//

        /** @brief The member's status in the chat, always “kicked” */
        const Status status = Status::KICKED;

        /** @brief Information about the user */
        User user;

        /** @brief Date when restrictions will be lifted for this user; unix time. If 0, then the user is banned forever */
        qint32 until_date;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBERBANNED_H
