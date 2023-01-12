#ifndef TELEGRAM_TYPES_CHATPERMISSIONS_H
#define TELEGRAM_TYPES_CHATPERMISSIONS_H

#include <compare>
#include <optional>

#include "qjsonobject.h"
#include "qstring.h"

namespace Telegram
{
    /**
     *
     * @brief This struct represent information about actions that a non-administrator user is allowed to take in a chat
     *
     */

    struct ChatPermissions
    {
        /** @brief Constructs Chat object from parameters, constructs an empty object if no parameters are passed */
        ChatPermissions(const std::optional<bool>& can_send_messages = std::nullopt,
                        const std::optional<bool>& can_send_media_messages = std::nullopt,
                        const std::optional<bool>& can_send_polls = std::nullopt,
                        const std::optional<bool>& can_send_other_messages = std::nullopt,
                        const std::optional<bool>& can_add_web_page_previews = std::nullopt,
                        const std::optional<bool>& can_change_info = std::nullopt,
                        const std::optional<bool>& can_invite_users = std::nullopt,
                        const std::optional<bool>& can_pin_messages = std::nullopt);

        /** @brief JSON constructor. Constructs ChatPermissions object from QJsonObject
        *
        * QJsonObject which is passed to constuctor has to has all key-value pairs related to ChatPermissions class fields. For example it should contain pairs such as "can_send_messages" = "...",
        * "can_send_media_messages" = "..." and so on, otherwise fields related to missing pairs will be setted to std::nullopt */
        ChatPermissions(const QJsonObject& json_object);


        /* @brief Returns ChatPermissions in form of JSON object. Returns empty QJsonObject if ChatPermissions is empty */
        QJsonObject toObject() const;

        /* @brief Returns true if ChatPermissions is empty */
        bool isEmpty() const;


        std::partial_ordering operator <=> (const ChatPermissions&) const = default;


//** Fields **//

        /** @brief Optional. True, if the user is allowed to send text messages, contacts, locations and venues */
        std::optional<bool> can_send_messages;
        
        /** @brief Optional. True, if the user is allowed to send audios, documents, photos, videos, video notes and voice notes, implies can_send_messages */
        std::optional<bool> can_send_media_messages;
        
        /** @brief Optional. True, if the user is allowed to send polls, implies can_send_messages */
        std::optional<bool> can_send_polls;
        
        /** @brief Optional. True, if the user is allowed to send animations, games, stickers and use inline bots, implies can_send_media_messages */
        std::optional<bool> can_send_other_messages;
        
        /** @brief Optional. True, if the user is allowed to add web page previews to their messages, implies can_send_media_messages */
        std::optional<bool> can_add_web_page_previews;
        
        /** @brief Optional. True, if the user is allowed to change the chat title, photo and other settings. Ignored in public supergroups */
        std::optional<bool> can_change_info;
        
        /** @brief Optional. True, if the user is allowed to invite new users to the chat */
        std::optional<bool> can_invite_users;
        
        /** @brief Optional. True, if the user is allowed to pin messages. Ignored in public supergroups */
        std::optional<bool> can_pin_messages;
    };
}

#endif // CHATPERMISSIONS_H
