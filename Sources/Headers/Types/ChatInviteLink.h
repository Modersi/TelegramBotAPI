#ifndef TELEGRAM_TYPES_CHATINVITELINK_H
#define TELEGRAM_TYPES_CHATINVITELINK_H

#include <compare>
#include <optional>

#include "qjsonobject.h"
#include "qstring.h"

#include "User.h"

namespace Telegram
{
    /**
     *
     * @brief Represents an invite link for a chat
     *
     */

    struct ChatInviteLink
    {
        /** @brief Default constructor. Constructs an empty ChatInviteLink object
         *
         * All fields setted to 0, "", etc... All optional fields setted to std::nullopt */
        ChatInviteLink();

        /** @brief Constructs ChatInviteLink object from parameters */
        ChatInviteLink(const QString& invite_link,
                       const User& creator,
                       const bool& is_primary,
                       const bool& is_revoked,
                       const std::optional<qint32>& expire_date = std::nullopt,
                       const std::optional<qint32>& member_limit = std::nullopt);

        /** @brief JSON constructor. Constructs ChatInviteLink object from QJsonObject
         *
         * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatInviteLink class fields. For example it should contain pairs such as "invite_link" = "...",
         * "creator" = "..." and so on, otherwise fields related to missing pairs will be setted to some default values(0, "", std::nullopt) */
        ChatInviteLink(const QJsonObject& json_object);


        /* @brief Returns ChatInviteLink in form of JSON object. Returns empty QJsonObject if ChatInviteLink is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ChatInviteLink is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ChatInviteLink&) const = default;


//** Fields **//

        /** @brief The invite link 
         * 
         *  If the link was created by another chat administrator, then the second part of the link will be replaced with "..." */
        QString invite_link;
        
        /** @brief Creator of the link */
        User creator;
        
        /** @brief True, if the link is primary */
        bool is_primary;
        
        /** @brief True, if the link is revoked */
        bool is_revoked;
        
        /** @brief Optional. Point in time (Unix timestamp) when the link will expire or has been expired */
        std::optional<qint32> expire_date;
        
        /** @brief Optional. Maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999 */
        std::optional<qint32> member_limit;   
    };
}

#endif // TELEGRAM_TYPES_CHATINVITELINK_H

