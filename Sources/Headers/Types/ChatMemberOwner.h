#ifndef TELEGRAM_TYPES_CHATMEMBEROWNER_H
#define TELEGRAM_TYPES_CHATMEMBEROWNER_H

#include <compare>
#include <optional>

#include "qstring.h"
#include "qjsonobject.h"

#include "User.h"
#include "ChatMember.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents a chat member that owns the chat and has all administrator privileges
     *
     */

    struct ChatMemberOwner : public ChatMember
    {
        /** @brief Default constructor. Constructs an empty object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatMemberOwner();

        /** @brief Constructs ChatMemberOwner object from parameters */
        ChatMemberOwner(const User& user,
                        const bool& is_anonymous,
                        const std::optional<QString>& custom_title = std::nullopt);

        /** @brief JSON constructor. Constructs ChatMemberOwner object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatMemberOwner class fields. For example it should contain pairs such as "user" = "...",
         * "status" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatMemberOwner(const QJsonObject& json_object);


        /* @brief Returns ChatMemberOwner in form of JSON object. Returns empty QJsonObject if ChatMemberOwner is empty */
        virtual QJsonObject toObject() const override;

        /* @brief Returns true if ChatMemberOwner is empty */
        virtual bool isEmpty() const override;

        /** @brief Returns status of the ChatMember */
        virtual Status getStatus() const override;


        std::partial_ordering operator <=> (const ChatMemberOwner&) const = default;

//** Fields **//

        /** @brief The member's status in the chat, always “creator” */
        const Status status = Status::CREATOR;

        /** @brief Information about the user */
        User user;

        /** @brief True, if the user's presence in the chat is hidden */
        bool is_anonymous;

        /** @brief Optional. Custom title for this user */
        std::optional<QString> custom_title;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBEROWNER_H
