#ifndef TELEGRAM_TYPES_CHATMEMBERUPDATED_H
#define TELEGRAM_TYPES_CHATMEMBERUPDATED_H

#include <compare>
#include <memory>
#include <optional>

#include "qjsonobject.h"

#include "Chat.h"
#include "ChatMember.h"
#include "ChatInviteLink.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represents changes in the status of a chat member
     *
     */

    struct ChatMemberUpdated
    {
        /** @brief Default constructor. Constructs an empty ChatMemberUpdated object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatMemberUpdated();

        /** @brief Constructs ChatMemberUpdated object from parameters */
        ChatMemberUpdated(const Chat& chat,
                          const User& from,
                          const qint32& date,
                          const std::shared_ptr<ChatMember>& old_chat_member,
                          const std::shared_ptr<ChatMember>& new_chat_member,
                          const std::optional<ChatInviteLink>& invite_link = std::nullopt);

        /** @brief JSON constructor. Constructs ChatMemberUpdated object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatMemberUpdated class fields. For example it should contain pairs such as "chat" = "...",
         * "from" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatMemberUpdated(const QJsonObject& json_object);

        /* @brief Returns ChatMemberUpdated in form of JSON object. Returns empty QJsonObject if ChatMemberUpdated is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ChatMemberUpdated is empty */
        bool isEmpty() const;

        std::partial_ordering operator <=> (const ChatMemberUpdated&) const = default;

//** Fields **//

        /** @brief Chat the user belongs to */
        Chat chat;
        
        /** @brief Performer of the action, which resulted in the change */
        User from;
        
        /** @brief Date the change was done in Unix time */
        qint32 date;
        
        /** @brief Previous information about the chat member */
        std::shared_ptr<ChatMember> old_chat_member;
        
        /** @brief New information about the chat member */
        std::shared_ptr<ChatMember> new_chat_member;
        
        /** @brief Optional. Chat invite link, which was used by the user to join the chat; for joining by invite link events only */
        std::optional<ChatInviteLink> invite_link;
    };
}

#endif // TELEGRAM_TYPES_CHATMEMBERUPDATED_H

